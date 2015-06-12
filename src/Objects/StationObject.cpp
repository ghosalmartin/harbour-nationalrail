#include "StationObject.h"

StationObject::StationObject(int id, QString station, bool favorited)
{
    m_id = id;
    m_station = station;
    m_favorited = favorited;
}

int StationObject::getID() const{
    return m_id;
}

QString StationObject::getStation() const{
    return m_station;
}

bool StationObject::getFavorited() const{
    return m_favorited;
}

void StationObject::setFavorited(bool favorited){
    m_favorited = favorited;
}
