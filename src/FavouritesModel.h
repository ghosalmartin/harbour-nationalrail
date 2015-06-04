#ifndef FAVOURITESMODEL_H
#define FAVOURITESMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <StationObject.h>
#include <Database.h>

class FavouritesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FavouritesModel();

    enum Roles {
            idRole = Qt::UserRole,
            stationRole = Qt::UserRole + 1,
            favoritedRole = Qt::UserRole + 2,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const { return _roles; }
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void retrieveData();
private:
    QList<StationObject> _data;
    QHash<int, QByteArray> _roles;
    //Database database;
};

#endif // FAVOURITESMODEL_H



