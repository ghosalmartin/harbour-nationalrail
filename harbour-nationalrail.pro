# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-nationalrail

CONFIG += sailfishapp

database.files = database/stationsDB.sqlite
database.path = /usr/share/harbour-nationalrail/data
INSTALLS += database


SOURCES += \
    src/Network/XMLGenerator.cpp \
    src/Network/NetworkRequest.cpp \
    src/Models/ServiceModel.cpp \
    src/Models/StationsModel.cpp \
    src/Models/FavouritesModel.cpp \
    src/Filter/StationsFilterModel.cpp \
    src/Database/Database.cpp \
    src/Objects/StationObject.cpp \
    src/Objects/ServiceObject.cpp \
    src/Database/DatabaseOperations.cpp \
    src/harbour-nationalrail.cpp \
    src/Objects/MessageObject.cpp \
    src/Models/MessagesModel.cpp \
    src/Objects/CallingPointObject.cpp \
    src/Models/PreviousCPModel.cpp \
    src/Models/SubsequentCPModel.cpp


HEADERS += \
    src/Network/XMLGenerator.h \
    src/Network/NetworkRequest.h \
    src/Objects/ServiceObject.h \
    src/Objects/StationObject.h \
    src/Models/ServiceModel.h \
    src/Models/StationsModel.h \
    src/Models/FavouritesModel.h\
    src/Filter/StationsFilterModel.h \
    src/Database/Database.h \
    src/Database/DatabaseOperations.h \
    src/Objects/MessageObject.h \
    src/Models/MessagesModel.h \
    src/Objects/CallingPointObject.h \
    src/Models/PreviousCPModel.h \
    src/Models/SubsequentCPModel.h


INCLUDEPATH += src/ \
    src/Database/ \
    src/Filter/ \
    src/Models/ \
    src/Network/ \
    src/Objects/

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/harbour-nationalrail.spec \
    rpm/harbour-nationalrail.yaml \
    translations/*.ts \
    qml/pages/Search.qml \
    qml/pages/LocationSearch.qml \
    qml/pages/Home.qml \
    database/stationsData.sql \
    database/stationsDB.sqlite \
    harbour-nationalrail.desktop \
    qml/harbour-nationalrail.qml \
    qml/pages/SearchResults.qml \
    qml/pages/Settings.qml \
    qml/pages/StationMessages.qml \
    qml/pages/JourneyDetails.qml \
    rpm/harbour-nationalrail.changes

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n



QT+= core xml sql


# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-nationalrail-de.ts

