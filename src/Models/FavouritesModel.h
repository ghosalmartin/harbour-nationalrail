#ifndef FAVOURITESMODEL_H
#define FAVOURITESMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <StationObject.h>
#include <StationsModel.h>
#include <Database.h>

class StationsModel;

class FavouritesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(StationsModel * stationsModel READ getStationsModel WRITE setStationsModel NOTIFY stationsModelChanged)
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
    StationsModel *getStationsModel () const { return m_stationsmodel; }
    void setStationsModel(StationsModel *source);

signals:
    void stationsModelChanged();
    void favouriteRemoved();

public slots:
    void updateFavourites();

private:
    QList<StationObject> _data;
    QHash<int, QByteArray> _roles;
    StationsModel *m_stationsmodel;
};

#endif // FAVOURITESMODEL_H



