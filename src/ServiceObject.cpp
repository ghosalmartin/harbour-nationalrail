#include "serviceobject.h"

ServiceObject::ServiceObject(QString stationName, QString stationCRS,QString destination, QString destinationCRS, QString departureTime, QString amendedDepartureTime, QString arrivalTime, QString amendedArrivalTime, QString platform, QString trainOperator, QString trainOperatorCode, QString serviceID)
{
    m_stationName = stationName;
    m_stationCRS = stationCRS;
    m_destination = destination;
    m_destinationCRS = destinationCRS;
    m_departureTime = departureTime;
    m_amendedDepartureTime = amendedDepartureTime;
    m_arrivalTime = arrivalTime;
    m_amendedArrivalTime = amendedArrivalTime;
    m_platform = platform;
    m_operator = trainOperator;
    m_operatorCode = trainOperatorCode;
    m_serviceID = serviceID;
}

QString ServiceObject::getStationName(){
    return m_stationName;
}

QString ServiceObject::getStationCRS(){
    return m_stationCRS;
}

QString ServiceObject::getDestination(){
    return m_destination;
}

QString ServiceObject::getDestinationCRS(){
    return m_destinationCRS;
}

QString ServiceObject::getDepartureTime(){
    return m_departureTime;
}

QString ServiceObject::getAmendedDepartureTime(){
    return m_amendedDepartureTime;
}

QString ServiceObject::getArrivalTime(){
    return m_arrivalTime;
}

QString ServiceObject::getAmendedArrivalTime(){
    return m_amendedArrivalTime;
}

QString ServiceObject::getPlatform(){
    return m_platform;
}

QString ServiceObject::getTrainOperator(){
    return m_operator;
}

QString ServiceObject::getOperatorCode(){
    return m_operatorCode;
}

QString ServiceObject::getServiceID(){
    return m_serviceID;
}
