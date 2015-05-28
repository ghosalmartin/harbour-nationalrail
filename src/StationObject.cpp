#include "StationObject.h"

StationObject::StationObject(int id, QString station, bool favourited)
{
    m_id = id;
    m_station = station;
    m_favourited = favourited;
}

int StationObject::getID(){

    return m_id;
}

QString StationObject::getStation(){
    return m_station;
}

bool StationObject::getFavorited(){

    return m_favourited;
}
