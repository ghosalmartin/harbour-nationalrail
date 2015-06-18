#include "CallingPointObject.h"

CallingPointObject::CallingPointObject(QString location, QString crs, QString scheduledTime, QString actualTime)
{
    m_location = location;
    m_crs = crs;
    m_scheduledTime = scheduledTime;
    m_actualTime = actualTime;
}

QString CallingPointObject::getLocation(){
    return m_location;
}

QString CallingPointObject::getCRS(){
    return m_crs;
}

QString CallingPointObject::getScheduledTime(){
    return m_scheduledTime;
}

QString CallingPointObject::getActualTime(){
    return m_actualTime;
}

