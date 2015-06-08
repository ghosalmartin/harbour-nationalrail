#ifndef STATIONOBJECT_H
#define STATIONOBJECT_H

#include <QObject>

class StationObject
{

public:
    explicit StationObject(int id, QString station, bool favorited);
    int getID() const;
    QString getStation() const;
    bool getFavorited() const;
    void setFavorited(bool favorited);
signals:

public slots:

private:
   int m_id;
   QString m_station;
   bool m_favorited;
};

#endif // STATIONOBJECT_H
