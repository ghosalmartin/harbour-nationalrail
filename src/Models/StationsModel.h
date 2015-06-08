#ifndef STATIONSMODEL_H
#define STATIONSMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <StationObject.h>
#include <Database.h>
#include <FavouritesModel.h>

class FavouritesModel;

class StationsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(FavouritesModel * favouriteModel READ getFavouritesModel WRITE setFavouritesModel NOTIFY favouritesModelChanged)
public:
    explicit StationsModel();

    enum Roles {
            idRole = Qt::UserRole,
            stationRole = Qt::UserRole + 1,
            favoritedRole = Qt::UserRole + 2,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const { return _roles; }
    void appendRow(StationObject station);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void retrieveData();
    FavouritesModel *getFavouritesModel () const { return m_favouritesmodel; }
    void setFavouritesModel(FavouritesModel *favouritesModel);

private:
    QList<StationObject> _data;
    QHash<int, QByteArray> _roles;
    FavouritesModel *m_favouritesmodel;

signals:
    void favouritesChanged();
    void favouritesModelChanged();

public slots:
    void removeFavourite();
};

#endif // STATIONSMODEL_H
