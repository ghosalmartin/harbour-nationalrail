#include "DatabaseOperations.h"

#include <QSqlQuery>
#include <QSqlResult>

DatabaseOperations::DatabaseOperations(QSqlDatabase db): m_db(db)
{

}

QList<StationObject> DatabaseOperations::getAllStations(){

    QSqlQuery query(m_db);
    QList<StationObject> stations;
    query.exec("SELECT * FROM stations");

    while(query.next()){
        StationObject station(query.value(0).toInt(0),query.value(1).toString(),query.value(3).toBool());
        stations.append(station);
    }

    return stations;
}

