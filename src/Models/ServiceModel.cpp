#include "servicemodel.h"
#include <QListIterator>
#include <QDebug>

ServiceModel::ServiceModel() : QAbstractListModel(), m_networkRequest(0)
{
    roles_[stationNameRole] = "stationName";
    roles_[stationCRSRole] = "stationCRS";
    roles_[destinationRole] = "destination";
    roles_[destinationCRSRole] = "destinationCRS";
    roles_[departureTimeRole] = "departureTime";
    roles_[amendedDepartureTimeRole] = "amendedDepartureTime";
    roles_[arrivalTimeRole] = "arrivalTime";
    roles_[amendedArrivalTimeRole] = "amendedArrivalTime";
    roles_[platformRole] = "platform";
    roles_[operatorRole] ="operator";
    roles_[operatorCodeRole] = "operatorCode";
    roles_[serviceIDRole] = "serviceID";
}

int ServiceModel::rowCount(const QModelIndex &) const
{
    return data_.size();
}

QVariant ServiceModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    if (row < 0 || row > data_.size()) return QVariant();
    ServiceObject serviceObject = data_.at(row);
    switch (role)
    {

    case stationNameRole : return serviceObject.getStationName();
    case stationCRSRole : return serviceObject.getStationCRS();
    case destinationRole: return serviceObject.getDestination();
    case destinationCRSRole : return serviceObject.getDestinationCRS();
    case departureTimeRole : return serviceObject.getDepartureTime();
    case amendedDepartureTimeRole : return serviceObject.getAmendedDepartureTime();
    case arrivalTimeRole : return serviceObject.getArrivalTime();
    case amendedArrivalTimeRole : return serviceObject.getAmendedArrivalTime();
    case platformRole : return serviceObject.getPlatform();
    case operatorRole : return serviceObject.getTrainOperator();
    case operatorCodeRole : return serviceObject.getOperatorCode();
    case serviceIDRole : return serviceObject.getServiceID();
    default: return QVariant();
    }

}
QHash<int, QByteArray> ServiceModel::roleNames() const

{
    return roles_;
}

void ServiceModel::appendRow(ServiceObject service)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    data_.append(service);
    endInsertRows();
}

void ServiceModel::populateModel(QList<ServiceObject> services){

    beginResetModel();

    data_.clear();

    QListIterator<ServiceObject> iterator(services);
    while(iterator.hasNext()){
        appendRow(iterator.next());
    }

    endResetModel();

    setReady(true);
}

void ServiceModel::setSource(NetworkRequest *source){
    if (m_networkRequest != source) {
        if (m_networkRequest) {
            disconnect(m_networkRequest, SIGNAL(dataProcessed(QList<ServiceObject>)), this, SLOT(populateModel(QList<ServiceObject>)));
        }
        m_networkRequest = source;
        if (m_networkRequest) {
            connect(m_networkRequest, SIGNAL(dataProcessed(QList<ServiceObject>)), this, SLOT(populateModel(QList<ServiceObject>)));
        }
        emit sourceChanged();
    }
}

void ServiceModel::setReady(bool ready){
    if (m_ready != ready) {
        m_ready = ready;
        emit readyChanged();
    }

}
