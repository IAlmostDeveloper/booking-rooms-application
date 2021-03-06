QT += quick
QT += network
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += cpp/Auth/Authmanager.cpp \
    cpp/Calendar/Calendarday.cpp \
    cpp/Calendar/Customcalendarmodel.cpp \
    cpp/Hotels/Hotelobjdect.cpp \
    cpp/Hotels/HotelsManager.cpp \
    cpp/Rents/Rentobject.cpp \
    cpp/Rents/RentsManager.cpp \
    cpp/Rooms/Roomobject.cpp \
    cpp/Rooms/RoomsManager.cpp \
    cpp/App.cpp \
    cpp/Session.cpp \
    main.cpp \
    cpp/Rents/Rentsmodel.cpp \
    cpp/Rooms/Roomsmodel.cpp \
    cpp/Hotels/Hotelsmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpp/Auth/Authmanager.hpp \
    cpp/Calendar/Calendarday.hpp \
    cpp/Calendar/Customcalendarmodel.hpp \
    cpp/Hotels/Hotelobjdect.hpp \
    cpp/Hotels/HotelsManager.hpp \
    cpp/Rents/Rentobject.hpp \
    cpp/Rents/RentsManager.hpp \
    cpp/Rooms/Roomobject.hpp \
    cpp/Rooms/RoomsManager.hpp \
    cpp/App.hpp \
    cpp/Session.hpp \
    cpp/Rents/Rentsmodel.hpp \
    cpp/Rooms/Roomsmodel.hpp \
    cpp/Hotels/Hotelsmodel.hpp

DISTFILES += \
    Forms/LoginForm.qml \
    Forms/MainForm.qml \
    Forms/RegisterForm.qml \
    InfoBlocks/RoomsBlock.qml \
    InfoBlocks/RentsBlock.qml \
    InfoBlocks/HotelsBlock.qml
