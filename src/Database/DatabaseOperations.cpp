#include "DatabaseOperations.h"

#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>

DatabaseOperations::DatabaseOperations()
{
    QSqlDatabase database = QSqlDatabase::database("stationsDB");
    m_db = database;
}

QList<StationObject> DatabaseOperations::getAllStations(){

    QSqlQuery query(m_db);
    QList<StationObject> stations;
    query.exec("SELECT * FROM stations");

    while(query.next()){
        StationObject station(query.value(0).toInt(0),query.value(1).toString(),query.value(2).toBool());
        stations.append(station);
    }

    return stations;
}

bool DatabaseOperations::updateFavourite(bool favourite, int id){



    int conversion = 0;

    if(favourite){
        conversion = 1;
    }

    QSqlQuery query(m_db);
    QString sql = QString("UPDATE stations SET favourite=%1 WHERE id=%2;").arg(conversion).arg(id);
    return query.exec(sql);
}

QList<StationObject> DatabaseOperations::getAllFavouriteStations(){

    QSqlQuery query(m_db);
    QList<StationObject> stations;
    query.exec("SELECT * FROM stations WHERE favourite=1");

    while(query.next()){
        StationObject station(query.value(0).toInt(0),query.value(1).toString(),query.value(2).toBool());
        stations.append(station);
    }

    return stations;
}



