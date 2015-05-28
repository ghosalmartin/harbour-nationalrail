#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <QObject>
#include <ServiceObject.h>
#include <QAbstractListModel>

class ServiceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ServiceModel();

    enum Roles {
            stationNameRole = Qt::UserRole + 1,
            stationCRSRole = Qt::UserRole + 2,
            destinationRole = Qt::UserRole + 3,
            destinationCRSRole = Qt::UserRole + 4,
            departureTimeRole = Qt::UserRole + 5,
            amendedTimeRole = Qt::UserRole + 6,
            platformRole = Qt::UserRole + 7,
            operatorRole = Qt::UserRole + 8,
            operatorCodeRole = Qt::UserRole + 9,
            serviceIDRole = Qt::UserRole + 10,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void appendRow(ServiceObject service);

signals:

public slots:
    void populateModel(QList<ServiceObject> services);
private:
    QList<ServiceObject> data_;
    QHash<int, QByteArray> roles_;

};

#endif // SERVICEMODEL_H
