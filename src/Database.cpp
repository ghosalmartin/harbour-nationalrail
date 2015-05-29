#include "database.h"

#include <QDir>

QString const databaseFolder ="/home/nemo/.harbour-nationalrail/";
QString const databaseName ="stationsDB.sqlite";

Database::Database()
{
    openDB();
}

Database::~Database()
{
    db.close();
}

bool Database::openDB()
{

    db = QSqlDatabase::addDatabase("QSQLITE");


    QString databasePath = databaseFolder + "/" + databaseName;

    db.setDatabaseName(databasePath);

    return db.open();
}

QSqlDatabase Database::getDB(){
    return db;
}
