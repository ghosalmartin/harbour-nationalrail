#include "StationsModel.h"
#include "StationObject.h"
#include "DatabaseOperations.h"
#include "Database.h"
#include <QDebug>

StationsModel::StationsModel() :
    QAbstractListModel()
{
    DatabaseOperations dbOp(database.getDB());
    _data = dbOp.getAllStations();

    _roles[idRole] = "id";
    _roles[stationRole] = "station";
    _roles[favoritedRole] = "favorited";
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
    case idRole: return stationObject.getID();
    case stationRole : return stationObject.getStation();
    case favoritedRole : return stationObject.getFavorited();
    default: return QVariant();
    }
}

void StationsModel::appendRow(StationObject station)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _data.append(station);
    endInsertRows();
}


bool StationsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
    case stationRole:
        return false;
    case favoritedRole: {
        bool newVal = value.toBool();
        _data[index.row()].setFavorited(newVal);
        DatabaseOperations dbOp(database.getDB());
        dbOp.updateFavourite(newVal, index.row()+1);
        return true;
    }
    default:
        return false;
    }
}
