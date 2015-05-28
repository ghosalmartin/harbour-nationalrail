#include "StationsModel.h"
#include "StationObject.h"
#include "Database.h"
#include "DatabaseOperations.h"

StationsModel::StationsModel() :
    QAbstractListModel()
{

    Database database;
    DatabaseOperations dbOp(database.getDB());
    _data = dbOp.getAllStations();

    _roles[stationRole] = "station";
    _roles[favouritedRole] = "favourited";
}

int StationsModel::rowCount(const QModelIndex &) const
{
    return _data.size();
}

QVariant StationsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > _data.size()) return QVariant();
    StationObject stationObject = _data.at(row);
    switch (role)
    {
    case stationRole : return stationObject.getStation();
    case favouritedRole : return stationObject.getFavorited();
    default: return QVariant();
    }
}

void StationsModel::appendRow(StationObject station)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _data.append(station);
    endInsertRows();
}
