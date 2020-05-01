from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import re
from database import DatabaseManager
import secrets

adminSessionTokens = []
userSessionTokens = []


class requestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed = re.split(', |=|\\?|/|&|', self.path)
        parsed.remove('')
        if not parsed.__contains__('token'):
            self.send_error(403)
        token = parsed[2]
        if userSessionTokens.__contains__(token) or adminSessionTokens.__contains__(token):
            self.send_response(200)
            self.send_header('content-type', 'application/json')
            self.end_headers()
            if parsed[0] == 'hotels':
                hotelsList = DatabaseManager.getHotels()
                self.wfile.write(json.dumps(hotelsList).encode())

            if parsed[0] == 'available-hotels':
                hotelsList = DatabaseManager.getAvailableHotels()
                self.wfile.write(json.dumps(hotelsList).encode())

            if parsed[0] == 'room':
                if len(parsed) < 5 or parsed[3] != 'room':
                    return
                roomsList = DatabaseManager.getRoomById(parsed[4])
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'rooms':
                roomsList = DatabaseManager.getRooms()
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'available-rooms':
                roomsList = DatabaseManager.getAvailableRooms()
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'hotel-rooms':
                if len(parsed) < 5 or parsed[3] != 'hotel':
                    return
                roomsList = DatabaseManager.getHotelRooms(parsed[4])
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'hotel-available-rooms':
                if len(parsed) < 5 or parsed[3] != 'hotel':
                    return
                roomsList = DatabaseManager.getHotelAvailableRooms(parsed[4])
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'rents':
                rentsList = DatabaseManager.getAllRents()
                self.wfile.write(json.dumps(rentsList).encode())

            if parsed[0] == 'room-rents':
                if len(parsed) < 5 or parsed[3] != 'room':
                    return
                rentsList = DatabaseManager.getRoomRents(parsed[4])
                self.wfile.write(json.dumps(rentsList).encode())

            if parsed[0] == 'user-rents':
                if len(parsed) < 5 or parsed[3] != 'user':
                    return
                rentsList = DatabaseManager.getRentsByLogin(parsed[4])
                self.wfile.write(json.dumps(rentsList).encode())

            if parsed[0] == 'clients':
                clientsList = DatabaseManager.getClients()
                self.wfile.write(json.dumps(clientsList).encode())

            if parsed[0] == 'users':
                if adminSessionTokens.__contains__(token):
                    usersList = DatabaseManager.getUsers()
                    self.wfile.write(json.dumps(usersList).encode())
        else:
            self.send_error(403)
            self.end_headers()

    def do_POST(self):
        content_len = int(self.headers.get('Content-Length'))
        post_body = self.rfile.read(content_len)
        jsonresult = json.loads(post_body)
        if self.path.split('/')[1] == 'add':
            if adminSessionTokens.__contains__(jsonresult["sessionToken"]):
                self.send_response(200)
                if self.path.endswith('/hotel'):
                    addHotel(jsonresult)
                if self.path.endswith('/room'):
                    addRoom(jsonresult)
                if self.path.endswith('/client'):
                    addClient(jsonresult)
                if self.path.endswith('/user'):
                    addUser(jsonresult)
            elif userSessionTokens.__contains__(jsonresult["sessionToken"]):
                self.send_response(200)
                if self.path.endswith('/rent'):
                    addRent(jsonresult)
                else:
                    self.send_error(403)
            else:
                self.send_error(403)
            self.end_headers()

        if self.path.split('/')[1] == 'delete':
            if adminSessionTokens.__contains__(jsonresult["sessionToken"]):
                self.send_response(200)
                if self.path.endswith('/hotel'):
                    deleteHotel(jsonresult)
                if self.path.endswith('/room'):
                    deleteRoom(jsonresult)
                if self.path.endswith('/rent'):
                    deleteRent(jsonresult)
                if self.path.endswith('/client'):
                    deleteClient(jsonresult)
                if self.path.endswith('/user'):
                    deleteUser(jsonresult)

                else:
                    self.send_error(403)
                self.end_headers()

        if self.path.split('/')[1] == 'update':
            if adminSessionTokens.__contains__(jsonresult["sessionToken"]):
                self.send_response(200)
                if self.path.endswith('/hotel'):
                    updateHotel(jsonresult)
                if self.path.endswith('/room'):
                    updateRoom(jsonresult)
                if self.path.endswith('/rent'):
                    updateRent(jsonresult)
                if self.path.endswith('/client'):
                    updateClient(jsonresult)
                if self.path.endswith('/user'):
                    updateUser(jsonresult)

            else:
                self.send_error(403)
            self.end_headers()

        if self.path.endswith('/register'):
            if registerUser(jsonresult["login"], jsonresult["password"], jsonresult["firstName"],
                            jsonresult["lastName"], jsonresult["passport"], jsonresult["rights"]) == 'ok':
                self.send_response(200)
            else:
                self.send_error(400)
            self.end_headers()

        if self.path.endswith('/auth'):
            token = authorizeUser(jsonresult['login'], jsonresult['password'])
            if token != 0:
                self.send_response(200)
                self.send_header('content-type', 'application/json')
            else:
                self.send_error(400)
            self.end_headers()
            self.wfile.write(json.dumps({
                'token': token,
                'login': jsonresult['login'],
                'isAdmin': adminSessionTokens.__contains__(token)
            }).encode())


def addHotel(jsonresult):
    DatabaseManager.addHotel(jsonresult["name"], jsonresult["address"],
                             jsonresult["description"], jsonresult["available"])


def addRoom(jsonresult):
    DatabaseManager.addRoom(jsonresult["hotel"], jsonresult["description"], jsonresult["available"])


def addRent(jsonresult):
    DatabaseManager.addRent(jsonresult["roomId"], jsonresult["userId"],
                            jsonresult["fromDate"], jsonresult["toDate"])


def addClient(jsonresult):
    DatabaseManager.addClient(jsonresult["userId"], jsonresult["firstName"],
                              jsonresult["lastName"], jsonresult["passport"])


def addUser(jsonresult):
    DatabaseManager.addUser(jsonresult["login"], jsonresult["password"], jsonresult["rights"])


def deleteHotel(jsonresult):
    DatabaseManager.deleteHotel(jsonresult["id"])


def deleteRoom(jsonresult):
    DatabaseManager.deleteRoom(jsonresult["id"])


def deleteRent(jsonresult):
    DatabaseManager.deleteRent(jsonresult["id"])


def deleteClient(jsonresult):
    DatabaseManager.deleteClient(jsonresult["id"])


def deleteUser(jsonresult):
    DatabaseManager.deleteUser(jsonresult["id"])


def updateHotel(jsonresult):
    DatabaseManager.updateHotel(jsonresult["id"], jsonresult["name"], jsonresult["address"],
                                jsonresult["description"], jsonresult["available"])


def updateRoom(jsonresult):
    DatabaseManager.updateRoom(jsonresult["id"], jsonresult["hotel"],
                               jsonresult["description"], jsonresult["available"])


def updateRent(jsonresult):
    DatabaseManager.updateRent(jsonresult["id"], jsonresult["roomId"], jsonresult["userId"],
                               jsonresult["fromDate"], jsonresult["toDate"])


def updateClient(jsonresult):
    DatabaseManager.updateClient(jsonresult["id"], jsonresult["userId"], jsonresult["firstName"],
                                 jsonresult["lastName"], jsonresult["passport"])


def updateUser(jsonresult):
    DatabaseManager.updateUser(jsonresult["id"], jsonresult["login"], jsonresult["password"], jsonresult["rights"])


def registerUser(login, password, firstName, lastName, passport, rights):
    if len(DatabaseManager.checkUser(login)) != 0:
        return "this login is already used"
    DatabaseManager.addUser(login, password, rights)
    userId = DatabaseManager.getUserId(login)[0]
    DatabaseManager.addClient(userId, firstName, lastName, passport)
    return "ok"


def authorizeUser(login, password):
    if len(DatabaseManager.getUser(login, password)) != 0:
        token = secrets.token_hex(20)
        rights = DatabaseManager.getUserRights(login)
        if rights[0] == 'admin':
            adminSessionTokens.append(token)
        else:
            userSessionTokens.append(token)
        return token
    else:
        return 0


def main():
    PORT = 8080
    serverAddress = ('localhost', PORT)
    server = HTTPServer(serverAddress, requestHandler)
    print("server running on port", PORT)
    DatabaseManager.createTables()
    server.serve_forever()


if __name__ == '__main__':
    main()
