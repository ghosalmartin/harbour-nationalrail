#include "FavouritesModel.h"
#include "DatabaseOperations.h"
#include <QDebug>
FavouritesModel::FavouritesModel() : QAbstractListModel()
{
    retrieveData();

    _roles[idRole] = "id";
    _roles[stationRole] = "station";
    _roles[favoritedRole] = "favorited";

}

int FavouritesModel::rowCount(const QModelIndex &) const
{
    return _data.size();
}

QVariant FavouritesModel::data(const QModelIndex &index, int role) const
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

bool FavouritesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
    case stationRole:
        return false;
    case favoritedRole: {
        bool newVal = value.toBool();
        DatabaseOperations dbOp;
        qDebug() << dbOp.updateFavourite(newVal, index.row()+1);
        emit favouriteRemoved();
        beginRemoveRows(index.parent(), index.row(), index.row());
        _data.removeAt(index.row());
        endRemoveRows();

        return true;
    }
    default:
        return false;
    }
}

void FavouritesModel::retrieveData(){
    DatabaseOperations dbOp;
    _data = dbOp.getAllFavouriteStations();
}

void FavouritesModel::updateFavourites(){
    beginResetModel();
    retrieveData();
    endResetModel();
}

void FavouritesModel::setStationsModel(StationsModel *stationsmodel){
    if (m_stationsmodel != stationsmodel) {
        if (m_stationsmodel) {
            disconnect(m_stationsmodel, SIGNAL(favouritesChanged()), this, SLOT(updateFavourites()));
        }
        m_stationsmodel = stationsmodel;
        if (m_stationsmodel) {
            connect(m_stationsmodel, SIGNAL(favouritesChanged()), this, SLOT(updateFavourites()));
        }
        emit stationsModelChanged();
    }
}
