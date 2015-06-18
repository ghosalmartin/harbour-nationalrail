#include "PreviousCPModel.h"

PreviousCPModel::PreviousCPModel() : QAbstractListModel(), m_networkRequest(0), m_ready(false)
{
    roles_[locationNameRole] = "locationName";
    roles_[crsRole] = "crs";
    roles_[scheduledTimeRole] = "scheduledTime";
    roles_[actualTimeRole] = "actualTime";
}

int PreviousCPModel::rowCount(const QModelIndex &) const
{
    return data_.size();
}

QVariant PreviousCPModel::data(const QModelIndex &index, int role) const
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
QHash<int, QByteArray> PreviousCPModel::roleNames() const

{
    return roles_;
}

void PreviousCPModel::appendRow(CallingPointObject callingpoint)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    data_.append(callingpoint);
    endInsertRows();
}

void PreviousCPModel::populateModel(QList<CallingPointObject> callingpoints){

    beginResetModel();

    data_.clear();

    data_ = callingpoints;

    endResetModel();

    setReady(true);
}

void PreviousCPModel::setSource(NetworkRequest *source){
    if (m_networkRequest != source) {
        if (m_networkRequest) {
            disconnect(m_networkRequest, SIGNAL(previousCallingPointsProcessed(QList<CallingPointObject>)), this, SLOT(populateModel(QList<CallingPointObject>)));
        }
        m_networkRequest = source;
        if (m_networkRequest) {
            connect(m_networkRequest, SIGNAL(previousCallingPointsProcessed(QList<CallingPointObject>)), this, SLOT(populateModel(QList<CallingPointObject>)));
        }
        emit sourceChanged();
    }
}

void PreviousCPModel::setReady(bool ready){
    if (m_ready != ready) {
        m_ready = ready;
        emit readyChanged();
    }
}
