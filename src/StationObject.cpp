#include "StationObject.h"

#include "QDebug"

StationObject::StationObject(int id, QString station, bool favorited)
{
    m_id = id;
    m_station = station;
    m_favorited = favorited;
}

int StationObject::getID(){
    return m_id;
}

QString StationObject::getStation(){
    return m_station;
}

bool StationObject::getFavorited(){
    return m_favorited;
}

void StationObject::setFavorited(bool favorited){
    m_favorited = favorited;
}
