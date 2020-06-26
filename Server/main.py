import json
from database import DatabaseManager
import secrets
from bottle import run, request, response, post, get, delete, put, default_app, HTTPResponse


@get('/hotels')
def getHotels():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getHotels()))


@get('/available-hotels')
def getAvailableHotels():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getAvailableHotels()))


@get('/rooms')
def getRooms():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getRooms()))


@get('/room')
def getRoom():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getRoomById(request.query['room'])))


@get('/available-rooms')
def getAvailableRooms():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getAvailableRooms()))


@get('/hotel-rooms')
def getHotelRooms():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getHotelRooms(request.query['hotel'])))


@get('/hotel-available-rooms')
def getHotelAvailableRooms():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getHotelAvailableRooms(request.query['hotel'])))


@get('/rents')
def getRents():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getAllRents()))


@get('/room-rents')
def getRoomRents():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getRoomRents(request.query['room'])))


@get('/user-rents')
def getUserRents():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    userId = DatabaseManager.getUserId(request.query['user'])
    _body = json.dumps(DatabaseManager.getUserRents(userId[0]))
    return HTTPResponse(status=200, body=_body)


@get('/clients')
def getClients():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getClients()))


@get('/users')
def getUsers():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    return HTTPResponse(status=200, body=json.dumps(DatabaseManager.getUsers()))


@get('user-rights')
def getUserRights():
    token = request.query['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
    return HTTPResponse(status=200, body=json.dumps({'rights': rights}))


@post('/hotel')
def addHotel():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.addHotel(body['name'], body['address'], body['description'], body['available'])
    return HTTPResponse(status=200)


@post('/room')
def addRoom():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.addRoom(body['hotel'], body['description'], body['available'])
    return HTTPResponse(status=200)


@post('/client')
def addClient():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.addClient(body['userId'], body['firstName'], body['lastName'], body['passport'])
    return HTTPResponse(status=200)


@post('/user')
def addUser():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)


@post('/user-rent')
def addUserRent():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    userId = DatabaseManager.getUserId(body['user'])[0]
    DatabaseManager.addRent(body['roomId'], userId, body['fromDate'], body['toDate'])
    return HTTPResponse(status=200)


@post('/rent')
def addRent():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.addRent(body['roomId'], body['userId'], body['fromDate'], body['toDate'])
    return HTTPResponse(status=200)


@put('/hotel')
def updateHotel():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.updateHotel(body['id'], body['name'], body['address'], body['description'], body['available'])
    return HTTPResponse(status=200)


@put('/room')
def updateRoom():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.updateRoom(body['id'], body['hotel'], body['description'], body['available'])
    return HTTPResponse(status=200)


@put('/rent')
def updateRent():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.updateRent(body['id'], body['roomId'], body['userId'], body['fromDate'], body['toDate'])
    return HTTPResponse(status=200)


@put('/client')
def updateClient():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.updateClient(body['id'], body['userId'], body['firstName'], body['lastName'], body['passport'])
    return HTTPResponse(status=200)


@put('/user')
def updateUser():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.updateUser(body['id'], body['login'], body['password'], body['rights'])
    return HTTPResponse(status=200)


@post('/delete/hotel')
def deleteHotel():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.deleteHotel(body['id'])
    return HTTPResponse(status=200)


@post('/delete/room')
def deleteRoom():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.deleteRoom(body['id'])
    return HTTPResponse(status=200)


@post('/delete/rent')
def deleteRent():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.deleteRent(body['id'])
    return HTTPResponse(status=200)


@post('/delete/client')
def deleteClient():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.deleteClient(body['userId'])
    return HTTPResponse(status=200)


@post('/delete/user')
def deleteUser():
    body = request.json
    token = body['token']
    if not DatabaseManager.checkSession(token):
        return HTTPResponse(status=401)
    else:
        rights = DatabaseManager.getUserRights(DatabaseManager.getLoginByToken(token)[0])[0]
        if rights != 'admin':
            return HTTPResponse(status=403)
    DatabaseManager.deleteUser(body['login'])
    return HTTPResponse(status=200)


@post('/auth')
def auth():
    body = request.json
    token = '0'
    isAdmin = False
    if len(DatabaseManager.getUser(body['login'], body['password'])) != 0:
        token = secrets.token_hex(20)
        DatabaseManager.addSession(body['login'], token)
        isAdmin = DatabaseManager.getUserRights([body['login']])[0] == 'admin'
    _response = {'error': 'Incorrect user data' if token == '0' else '', 'token': token, 'isAdmin': isAdmin}
    return HTTPResponse(status=200, body=json.dumps(_response))


@post('/register')
def register():
    body = request.json
    registered = registerUser(body['login'], body['password'], body['firstName'],
                              body['lastName'], body['passport'], body['rights'])
    _response = {'error': '' if registered else 'User already registered'}
    return HTTPResponse(status=200, body=json.dumps(_response))


def registerUser(login, password, firstName, lastName, passport, rights):
    if len(DatabaseManager.checkUser(login)) != 0:
        return False
    DatabaseManager.addUser(login, password, rights)
    userId = DatabaseManager.getUserId(login)[0]
    DatabaseManager.addClient(userId, firstName, lastName, passport)
    return True


DatabaseManager.createTables()
if __name__ == "__main__":
    run(host='127.0.0.1', port=8080, debug=True, reloader=True)
else:
    application = default_app()
