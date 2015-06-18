#include "SubsequentCPModel.h"

SubsequentCPModel::SubsequentCPModel(): QAbstractListModel(),m_networkRequest(0),m_ready(false)
{
    roles_[locationNameRole] = "locationName";
    roles_[crsRole] = "crs";
    roles_[scheduledTimeRole] = "scheduledTime";
    roles_[actualTimeRole] = "actualTime";
}

int SubsequentCPModel::rowCount(const QModelIndex &) const
{
    return data_.size();
}

QVariant SubsequentCPModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > data_.size()) return QVariant();
    CallingPointObject callingpoint = data_.at(row);
    switch (role)
    {

    case locationNameRole : return callingpoint.getLocation();
    case crsRole : return callingpoint.getCRS();
    case scheduledTimeRole: return callingpoint.getScheduledTime();
    case actualTimeRole : return callingpoint.getActualTime();
    default: return QVariant();
    }
}
QHash<int, QByteArray> SubsequentCPModel::roleNames() const

{
    return roles_;
}

void SubsequentCPModel::appendRow(CallingPointObject callingpoint)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    data_.append(callingpoint);
    endInsertRows();
}

void SubsequentCPModel::populateModel(QList<CallingPointObject> callingpoints){

    beginResetModel();

    data_.clear();

    data_ = callingpoints;

    endResetModel();

    setReady(true);
}

void SubsequentCPModel::setSource(NetworkRequest *source){
    if (m_networkRequest != source) {
        if (m_networkRequest) {
            disconnect(m_networkRequest, SIGNAL(subsequentCallingPointsProcessed(QList<CallingPointObject>)), this, SLOT(populateModel(QList<CallingPointObject>)));
        }
        m_networkRequest = source;
        if (m_networkRequest) {
            connect(m_networkRequest, SIGNAL(subsequentCallingPointsProcessed(QList<CallingPointObject>)), this, SLOT(populateModel(QList<CallingPointObject>)));
        }
        emit sourceChanged();
    }
}

void SubsequentCPModel::setReady(bool ready){
    if (m_ready != ready) {
        m_ready = ready;
        emit readyChanged();
    }
}
