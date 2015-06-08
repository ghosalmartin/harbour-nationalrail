#ifndef DATABASEOPERATIONS_H
#define DATABASEOPERATIONS_H

#include <QSqlDatabase>
#include <StationObject.h>

class DatabaseOperations
{

public:
    DatabaseOperations();
    QList<StationObject> getAllStations();
    QList<StationObject> getAllFavouriteStations();
    bool updateFavourite(bool favourite, int row);
private:
    QSqlDatabase m_db;
};

#endif // DATABASEOPERATIONS_H
