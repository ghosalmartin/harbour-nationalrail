#ifndef SERVICEOBJECT_H
#define SERVICEOBJECT_H

#include <QObject>

class ServiceObject
{

public:
    ServiceObject(QString, QString, QString, QString,QString,QString, QString, QString, QString,QString,QString, QString);
    QString getStationName();
    QString getStationCRS();
    QString getDestination();
    QString getDestinationCRS();
    QString getDepartureTime();
    QString getAmendedDepartureTime();
    QString getArrivalTime();
    QString getAmendedArrivalTime();
    QString getPlatform();
    QString getTrainOperator();
    QString getOperatorCode();
    QString getServiceID();


private:
    QString m_stationName;
    QString m_stationCRS;
    QString m_destination;
    QString m_destinationCRS;
    QString m_departureTime;
    QString m_amendedDepartureTime;
    QString m_arrivalTime;
    QString m_amendedArrivalTime;
    QString m_platform;
    QString m_operator;
    QString m_operatorCode;
    QString m_serviceID;
};

#endif // SERVICEOBJECT_H
