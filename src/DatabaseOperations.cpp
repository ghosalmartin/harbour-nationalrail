#include "DatabaseOperations.h"

#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>

DatabaseOperations::DatabaseOperations(QSqlDatabase db): m_db(db)
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

void DatabaseOperations::updateFavourite(int favourite, int row){

    QSqlQuery query(m_db);
    QString sql = "UPDATE stations SET favourited=";
    sql.append(favourite);
    sql.append(" WHERE id=");
    sql.append(row);
    qDebug() << sql;
    //query.exec(sql);


}

