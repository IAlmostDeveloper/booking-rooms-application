import sqlite3

conn = sqlite3.connect('hotels.db')
cursor = conn.cursor()


class DatabaseManager:
    @staticmethod
    def createTables():
        if len(cursor.execute("""SELECT name FROM sqlite_master WHERE type='table';""").fetchall()) == 0:
            cursor.execute("""create table hotels(
            id integer primary key,
            name text unique,
            address text,
            description text,
            available numeric
            )""")
            cursor.execute("""create table rooms(
            id integer primary key,
            hotel text,
            description text,
            available numeric        
            )""")
            cursor.execute("""create table rents(
            id integer primary key,
            roomId integer,
            userId integer,
            fromDate text,
            toDate text
            )""")
            cursor.execute("""create table clients(
            id integer primary key,
            userId integer,
            firstname text,
            lastname text,
            passport text unique
            )""")
            cursor.execute("""create table users(
            id integer primary key,
            login text unique,
            password text,
            rights text
            
            )""")
            DatabaseManager.fillDBWithExampleData()
        conn.commit()

    @staticmethod
    def fillDBWithExampleData():
        DatabaseManager.addHotel('Hotel1', 'Address1', 'Description1', 1)
        DatabaseManager.addHotel('Hotel2', 'Address2', 'Description2', 1)
        DatabaseManager.addHotel('Hotel3', 'Address3', 'Description3', 1)
        DatabaseManager.addRoom('Hotel2', 'Simple room', 0)
        DatabaseManager.addRoom('Hotel2', 'Cheap room', 1)
        DatabaseManager.addRoom('Hotel3', 'Expensive room', 1)
        DatabaseManager.addRoom('Hotel1', 'Another expensive room', 0)
        DatabaseManager.addUser('admin', 'admin', 'admin')

    @staticmethod
    def clearTable(tableName):
        cursor.execute("delete * from '{tableName}'".format(tableName=tableName))
        conn.commit()

    @staticmethod
    def addHotel(name, address, description, available):
        cursor.execute("insert into hotels(name, address, description, available) "
                       "values ('{name}' , '{address}', '{description}','{available}')"
                       .format(name=name, address=address, description=description, available=available))
        conn.commit()

    @staticmethod
    def addRoom(hotel, description, available):
        cursor.execute("insert into rooms(hotel, description, available) "
                       "values ('{hotel}', '{description}', '{available}')"
                       .format(hotel=hotel, description=description, available=available))
        conn.commit()

    @staticmethod
    def addRent(roomId, userId, fromDate, toDate):
        cursor.execute("insert into rents(roomId, userId, fromDate, toDate) "
                       "values ('{roomId}' , '{userId}', '{fromDate}', '{toDate}')"
                       .format(roomId=roomId, userId=userId, fromDate=fromDate, toDate=toDate))
        conn.commit()

    @staticmethod
    def addClient(userId, firstName, lastName, passport):
        cursor.execute("insert into clients(userId, firstName, lastName, passport) "
                       "values ('{userId}', '{firstName}' , '{lastName}', '{passport}')"
                       .format(userId=userId, firstName=firstName, lastName=lastName, passport=passport))
        conn.commit()

    @staticmethod
    def addUser(login, password, rights):
        cursor.execute("insert into users(login, password, rights) "
                       "values ('{login}' , '{password}', '{rights}')"
                       .format(login=login, password=password, rights=rights))
        conn.commit()

    @staticmethod
    def updateHotel(id, name, address, description, available):
        cursor.execute(
            "update hotels set name='{name}', address='{address}', "
            "description='{description}', available='{available}' where id='{id}'"
                .format(id=id, name=name, address=address, description=description, available=available))
        conn.commit()

    @staticmethod
    def updateRoom(id, hotel, description, available):
        cursor.execute(
            "update rooms set hotel='{hotel}', description='{description}', available='{available}' where id='{id}'"
            .format(id=id, hotel=hotel, description=description, available=available))
        conn.commit()

    @staticmethod
    def updateRent(id, roomId, userId, fromDate, toDate):
        cursor.execute("update rents set roomId='{roomId}', userId='{userId}', "
                       "fromDate='{fromDate}', toDate='{toDate}' where id='{id}'"
                       .format(id=id, roomId=roomId, userId=userId, fromDate=fromDate, toDate=toDate))
        conn.commit()

    @staticmethod
    def updateClient(id, userId, firstName, lastName, passport):
        cursor.execute("update clients set userId='{userId}', "
                       "firstname='{firstName}', lastname='{lastName}', passport='{passport}' where id='{id}'"
                       .format(id=id, userId=userId, firstName=firstName, lastName=lastName, passport=passport))
        conn.commit()

    @staticmethod
    def updateUser(id, login, password, rights):
        cursor.execute("update users set login='{login}', "
                       "password='{password}', rights='{rights}'where id='{id}'"
                       .format(id=id, login=login, password=password, rights=rights))
        conn.commit()

    @staticmethod
    def deleteHotel(id):
        cursor.execute("delete from hotels where id='{id}'".format(id=id))
        conn.commit()

    @staticmethod
    def deleteRoom(id):
        cursor.execute("delete from rooms where id='{id}'".format(id=id))
        conn.commit()

    @staticmethod
    def deleteRent(id):
        cursor.execute("delete from rents where id='{id}'".format(id=id))
        conn.commit()

    @staticmethod
    def deleteClient(userId):
        cursor.execute("delete from clients where userId='{userId}'"
                       .format(userId=userId))
        conn.commit()

    @staticmethod
    def deleteUser(login):
        cursor.execute("delete from users where login='{login}'".format(login=login))
        conn.commit()

    @staticmethod
    def getHotels():
        cursor.execute("select * from hotels")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getAvailableHotels():
        cursor.execute("select * from hotels where available=1")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getRooms():
        cursor.execute("select * from rooms")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getAvailableRooms():
        cursor.execute("select * from rooms where available=1")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getHotelRooms(hotel):
        cursor.execute("select * from rooms where hotel='{hotel}'".format(hotel=hotel))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getHotelAvailableRooms(hotel):
        cursor.execute("select * from rooms where hotel='{hotel}' and available=1".format(hotel=hotel))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getAllRents():
        cursor.execute("select * from rents")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getRoomRents(roomId):
        cursor.execute("select * from rents where roomId='{roomId}'".format(roomId=roomId))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getUserRents(userId):
        cursor.execute("select * from rents where userId='{userId}'".format(userId=userId))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getRentsByLogin(login):
        id = DatabaseManager.getUserId(login)[0];
        cursor.execute("select * from rents where userId='{id}'".format(id=id))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getClients():
        cursor.execute("select * from clients")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getUsers():
        cursor.execute("select * from users")
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def checkUser(login):
        cursor.execute("select * from users where login='{login}'".format(login=login))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getUser(login, password):
        cursor.execute("select * from users where login='{login}' and password='{password}'"
                       .format(login=login, password=password))
        conn.commit()
        return cursor.fetchall()

    @staticmethod
    def getUserId(login):
        cursor.execute("select id from users where login='{login}'"
                       .format(login=login))
        conn.commit()
        return cursor.fetchone()

    @staticmethod
    def getUserRights(login):
        cursor.execute("select rights from users where login='{login}'".format(login=login))
        conn.commit()
        return cursor.fetchone()
