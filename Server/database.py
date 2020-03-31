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
            available numeric,
            address text
            )""")
            cursor.execute("""create table rooms(
            id integer primary key,
            available numeric,
            description text
            )""")
            cursor.execute("""create table rents(
            id integer primary key,
            roomId integer,
            fromDate integer,
            toDate integer
            )""")
            cursor.execute("""create table clients(
            id integer primary key,
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
    def addHotel(name, available, address):
        cursor.execute(
            "insert into hotels(name, available, address) values ('{name}' , '{available}', '{address}')".format(
                name=name,
                available=available,
                address=address))
        conn.commit()

    @staticmethod
    def addRoom(available, description):
        cursor.execute(
            "insert into rooms(available, description) values ('{available}', '{description}')".format(
                available=available,
                description=description))
        conn.commit()

    @staticmethod
    def addRent(roomId, fromDate, toDate):
        cursor.execute(
            "insert into rents(roomId, fromDate, toDate) values ('{roomId}' , '{fromDate}', '{toDate}')".format(
                roomId=roomId,
                fromDate=fromDate,
                toDate=toDate))
        conn.commit()

    @staticmethod
    def addClient(firstName, lastName, passport):
        cursor.execute(
            "insert into clients(firstName, lastName, passport) values ('{firstName}' , '{lastName}', '{passport}')".format(
                firstName=firstName,
                lastName=lastName,
                passport=passport))
        conn.commit()

    @staticmethod
    def addUser(login, password, rights):
        cursor.execute(
            "insert into users(login, password, rights) values ('{login}' , '{password}', '{rights}')".format(
                login=login,
                password=password,
                rights=rights))
        conn.commit()

    @classmethod
    def getHotels(cls):
        cursor.execute("select * from hotels")
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getRooms(cls):
        cursor.execute("select * from rooms")
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getRents(cls):
        cursor.execute("select * from rents")
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getClients(cls):
        cursor.execute("select * from clients")
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getUsers(cls):
        cursor.execute("select * from users")
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def checkUser(cls, login):
        cursor.execute(
            "select * from users where login='{login}'".format(login=login))
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getUser(cls, login, password):
        cursor.execute(
            "select * from users where login='{login}' and password='{password}'".format(login=login,
                                                                                         password=password))
        conn.commit()
        result = cursor.fetchall()
        return result

    @classmethod
    def getUserRights(cls, login):
        cursor.execute(
            "select rights from users where login='{login}'".format(login=login))
        conn.commit()
        result = cursor.fetchone()
        return result
