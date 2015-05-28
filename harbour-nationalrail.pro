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
database.path = /home/nemo/.NationalRail
INSTALLS += database


SOURCES += \
    src/XMLGenerator.cpp \
    src/ServiceObject.cpp \
    src/NetworkRequest.cpp \
    src/ServiceModel.cpp \
    src/StationsModel.cpp \
    src/StationsFilterModel.cpp \
    src/Database.cpp \
    src/StationObject.cpp \
    src/DatabaseOperations.cpp \
    src/harbour-nationalrail.cpp

INCLUDEPATH += src/ \

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/harbour-nationalrail.changes.in \
    rpm/harbour-nationalrail.spec \
    rpm/harbour-nationalrail.yaml \
    translations/*.ts \
    qml/pages/Test.qml \
    qml/pages/Search.qml \
    qml/pages/LocationSearch.qml \
    qml/pages/Home.qml \
    database/stationsData.sql \
    database/stationsDB.sqlite \
    harbour-nationalrail.desktop \
    qml/harbour-nationalrail.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

HEADERS += \
    src/XMLGenerator.h \
    src/ServiceObject.h \
    src/NetworkRequest.h \
    src/ServiceModel.h \
    src/StationsModel.h \
    src/StationsFilterModel.h \
    src/Database.h \
    src/StationObject.h \
    src/DatabaseOperations.h

QT+= core xml sql


# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-nationalrail-de.ts

