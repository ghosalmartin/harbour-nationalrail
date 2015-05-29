#ifndef STATIONSMODEL_H
#define STATIONSMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <StationObject.h>

class StationsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StationsModel();

    enum Roles {
            idRole = Qt::UserRole,
            stationRole = Qt::UserRole + 1,
            favouritedRole = Qt::UserRole + 2,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const { return _roles; }
    void appendRow(StationObject station);

private:
    QList<StationObject> _data;
    QHash<int, QByteArray> _roles;

signals:

public slots:

};

#endif // STATIONSMODEL_H
