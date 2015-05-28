#include "database.h"

#include <QDir>

QString const databaseFolder ="/.NationalRail";
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

    QString databaseFolderPath=QDir::home().path()+ databaseFolder;
    QDir dir(databaseFolderPath);

    if(!dir.exists()){

        dir.mkdir(databaseFolderPath);

    }

    QString databasePath = databaseFolderPath + "/" + databaseName;

    db.setDatabaseName(databasePath);

    return db.open();
}

QSqlDatabase Database::getDB(){
    return db;
}
