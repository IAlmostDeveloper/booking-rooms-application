import sqlite3

conn = sqlite3.connect('hotels.db')
cursor = conn.cursor()


class DatabaseManager:
    @staticmethod
    def createTables():
        cursor.execute("""SELECT name FROM sqlite_master WHERE type='table';""")
        count = len(cursor.fetchall())
        if count == 0:
            cursor.execute("""create table hotels(
            id integer primary key,
            name text unique,
            address text,
            description text,
            available numeric
            )""")
            cursor.execute("""create table rooms(
            id integer primary key,
            hotelId integer,
            description text,
            available numeric        
            )""")
            cursor.execute("""create table rents(
            id integer primary key,
            roomId integer,
            userId integer,
            fromDate integer,
            toDate integer
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
        conn.commit()
        return count

    @staticmethod
    def addHotel(name, address, description, available):
        cursor.execute(
            "insert into hotels(name, address, description, available) "
            "values ('{name}' , '{address}', '{description}','{available}')".format(
                name=name,
                address=address,
                description=description,
                available=available
                ))
        conn.commit()

    @staticmethod
    def addRoom(hotelId, description, available):
        cursor.execute(
            "insert into rooms(hotelId, description, available) "
            "values ('{hotelId}', '{description}', '{available}')".format(
                hotelId=hotelId,
                description=description,
                available=available
            ))
        conn.commit()

    @staticmethod
    def addRent(roomId, userId, fromDate, toDate):
        cursor.execute(
            "insert into rents(roomId, userId, fromDate, toDate) "
            "values ('{roomId}' , '{userId}', '{fromDate}', '{toDate}')".format(
                roomId=roomId,
                userId=userId,
                fromDate=fromDate,
                toDate=toDate))
        conn.commit()

    @staticmethod
    def addClient(userId, firstName, lastName, passport):
        cursor.execute(
            "insert into clients(userId, firstName, lastName, passport) "
            "values ('{userId}', '{firstName}' , '{lastName}', '{passport}')".format(
                userId=userId,
                firstName=firstName,
                lastName=lastName,
                passport=passport))
        conn.commit()

    @staticmethod
    def addUser(login, password, rights):
        cursor.execute(
            "insert into users(login, password, rights) "
            "values ('{login}' , '{password}', '{rights}')".format(
                login=login,
                password=password,
                rights=rights))
        conn.commit()

    @classmethod
    def getHotels(cls):
        cursor.execute("select * from hotels")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getAvailableHotels(cls):
        cursor.execute("select * from hotels where available=1")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getRooms(cls):
        cursor.execute("select * from rooms")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getAvailableRooms(cls):
        cursor.execute("select * from rooms where available=1")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getHotelRooms(cls, hotelId):
        cursor.execute("select * from rooms where hotelId='{hotelId}'".format(hotelId=hotelId))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getHotelAvailableRooms(cls, hotelId):
        cursor.execute("select * from rooms where hotelId='{hotelId}' and available=1".format(hotelId=hotelId))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getAllRents(cls):
        cursor.execute("select * from rents")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getRoomRents(cls, roomId):
        cursor.execute("select * from rents where roomId='{roomId}'".format(roomId=roomId))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getUserRents(cls, userId):
        cursor.execute("select * from rents where userId='{userId}'".format(userId=userId))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getClients(cls):
        cursor.execute("select * from clients")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getUsers(cls):
        cursor.execute("select * from users")
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def checkUser(cls, login):
        cursor.execute("select * from users where login='{login}'".format(login=login))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getUser(cls, login, password):
        cursor.execute("select * from users where login='{login}' and password='{password}'"
                       .format(login=login, password=password))
        conn.commit()
        return cursor.fetchall()

    @classmethod
    def getUserRights(cls, login):
        cursor.execute("select rights from users where login='{login}'".format(login=login))
        conn.commit()
        return cursor.fetchone()
