#ifndef DATABASEOPERATIONS_H
#define DATABASEOPERATIONS_H

#include <QSqlDatabase>
#include <StationObject.h>

class DatabaseOperations
{
public:
    DatabaseOperations(QSqlDatabase m_db);
    QList<StationObject> getAllStations();
private:
    QSqlDatabase m_db;
};

#endif // DATABASEOPERATIONS_H
