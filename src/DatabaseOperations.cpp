#include "DatabaseOperations.h"

#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>

DatabaseOperations::DatabaseOperations(QSqlDatabase database):m_db(database)
{
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

void DatabaseOperations::updateFavourite(bool favourite, int id){
    QSqlQuery query(m_db);
    QString sql = QString("UPDATE stations SET favourite=%1 WHERE id=%2;").arg(favourite).arg(id);
    query.exec(sql);
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



