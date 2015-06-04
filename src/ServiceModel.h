#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include <ServiceObject.h>
#include <NetworkRequest.h>
class ServiceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(NetworkRequest * source READ getSource WRITE setSource NOTIFY sourceChanged)
public:
    explicit ServiceModel(QObject *parent = 0);

    enum Roles {
            stationNameRole = Qt::UserRole + 1,
            stationCRSRole = Qt::UserRole + 2,
            destinationRole = Qt::UserRole + 3,
            destinationCRSRole = Qt::UserRole + 4,
            departureTimeRole = Qt::UserRole + 5,
            amendedDepartureTimeRole = Qt::UserRole + 6,
            arrivalTimeRole = Qt::UserRole +7,
            amendedArrivalTimeRole = Qt::UserRole + 8,
            platformRole = Qt::UserRole + 9,
            operatorRole = Qt::UserRole + 10,
            operatorCodeRole = Qt::UserRole + 11,
            serviceIDRole = Qt::UserRole + 12,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void appendRow(ServiceObject service);
    NetworkRequest *getSource () const { return m_networkRequest; }
    void setSource(NetworkRequest *source);

signals:
    void sourceChanged();

public slots:
    void populateModel(QList<ServiceObject> services);
private:
    QList<ServiceObject> data_;
    QHash<int, QByteArray> roles_;
    NetworkRequest *m_networkRequest;

};

#endif // SERVICEMODEL_H
