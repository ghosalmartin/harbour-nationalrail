#ifndef CALLINGPOINTOBJECT_H
#define CALLINGPOINTOBJECT_H

#include <QString>

class CallingPointObject
{
public:
    CallingPointObject(QString location, QString crs, QString scheduledTime, QString actualTime);
    QString getLocation();
    QString getCRS();
    QString getScheduledTime();
    QString getActualTime();

private:
    QString m_location;
    QString m_crs;
    QString m_scheduledTime;
    QString m_actualTime;

};

#endif // CALLINGPOINTOBJECT_H
