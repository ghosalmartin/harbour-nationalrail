#ifndef DATABASEOPERATIONS_H
#define DATABASEOPERATIONS_H

#include <QSqlDatabase>
#include <StationObject.h>

class DatabaseOperations
{

public:
    DatabaseOperations(QSqlDatabase);
    QList<StationObject> getAllStations();
    QList<StationObject> getAllFavouriteStations();
    void updateFavourite(bool favourite, int row);
private:
    QSqlDatabase m_db;
};

#endif // DATABASEOPERATIONS_H
