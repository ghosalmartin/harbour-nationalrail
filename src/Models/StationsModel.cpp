#include "StationsModel.h"
#include "StationObject.h"
#include "DatabaseOperations.h"
#include "Database.h"
#include <QDebug>

StationsModel::StationsModel() : QAbstractListModel(),m_favouritesmodel(0)
{
    retrieveData();

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
        int id = _data.at(index.row()).getID();
        _data[index.row()].setFavorited(newVal);
        DatabaseOperations dbOp;
        dbOp.updateFavourite(newVal, id);
        emit favouritesChanged();
        return true;
    }
    default:
        return false;
    }
}

void StationsModel::removeFavourite(){
    beginResetModel();
    retrieveData();
    endResetModel();
}

void StationsModel::retrieveData(){
    DatabaseOperations dbOp;
    _data = dbOp.getAllStations();
}

void StationsModel::setFavouritesModel(FavouritesModel *favouritesmodel){

    if (m_favouritesmodel != favouritesmodel) {

        if (m_favouritesmodel){
            //No longer causing segfaults, had to initilize the model in constructor, thanks lukedirtwalker :)
            disconnect(m_favouritesmodel, SIGNAL(favouriteRemoved()), this, SLOT(removeFavourite()));

        }
        m_favouritesmodel = favouritesmodel;

        if (m_favouritesmodel) {
            connect(m_favouritesmodel, SIGNAL(favouriteRemoved()), this, SLOT(removeFavourite()));
        }

        emit favouritesModelChanged();
    }
}
