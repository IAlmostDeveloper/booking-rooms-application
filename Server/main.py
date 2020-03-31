from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import re
from database import DatabaseManager
import secrets

adminSessionTokens = []
userSessionTokens = []


class requestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed = re.split(', |=|\\?|/|', self.path)
        parsed.remove('')
        if not parsed.__contains__('token'):
            self.send_error(403)
        token = parsed[2]
        if userSessionTokens.__contains__(token) or adminSessionTokens.__contains__(token):
            self.send_response(200)
            self.send_header('content-type', 'application/json')
            if parsed[0] == 'hotels':
                hotelsList = DatabaseManager.getHotels()
                print(hotelsList)
                self.wfile.write(json.dumps(hotelsList).encode())

            if parsed[0] == 'rooms':
                roomsList = DatabaseManager.getRooms()
                self.wfile.write(json.dumps(roomsList).encode())

            if parsed[0] == 'rents':
                rentsList = DatabaseManager.getRents()
                self.wfile.write(json.dumps(rentsList).encode())

            if parsed[0] == 'clients':
                clientsList = DatabaseManager.getClients()
                self.wfile.write(json.dumps(clientsList).encode())

            if parsed[0] == 'users':
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
                    DatabaseManager.addHotel(jsonresult["name"],
                                             jsonresult["available"],
                                             jsonresult["address"])

                if self.path.endswith('/room'):
                    DatabaseManager.addRoom(jsonresult["available"],
                                            jsonresult["description"])

                if self.path.endswith('/rent'):
                    DatabaseManager.addRent(jsonresult["roomId"],
                                            jsonresult["fromDate"],
                                            jsonresult["toDate"])

                if self.path.endswith('/client'):
                    DatabaseManager.addClient(jsonresult["firstName"],
                                              jsonresult["lastName"],
                                              jsonresult["passport"])

                if self.path.endswith('/user'):
                    DatabaseManager.addUser(jsonresult["login"],
                                            jsonresult["password"],
                                            jsonresult["rights"])
            else:
                self.send_error(403)
            self.end_headers()

        if self.path.endswith('/register'):
            if registerUser(jsonresult['login'], jsonresult['password'], jsonresult['rights']) == 'ok':
                self.send_response(200)
            else:
                self.send_error(400)

        if self.path.endswith('/auth'):
            token = authorizeUser(jsonresult['login'], jsonresult['password'])
            if token != 0:
                self.send_response(200)
                self.send_header('content-type', 'application/json')
            else:
                self.send_error(400)
            self.end_headers()
            self.wfile.write(json.dumps({
                'token': token
            }).encode())


def registerUser(login, password, rights):
    if len(DatabaseManager.checkUser(login)) != 0:
        return "this login is already used"
    DatabaseManager.addUser(login, password, rights)
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
