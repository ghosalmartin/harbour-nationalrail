#ifndef STATIONOBJECT_H
#define STATIONOBJECT_H

#include <QObject>

class StationObject
{

public:
    explicit StationObject(int id, QString station, bool favourited);
    int getID();
    QString getStation();
    bool getFavorited();
signals:

public slots:

private:
   int m_id;
   QString m_station;
   bool m_favourited;
};

#endif // STATIONOBJECT_H
