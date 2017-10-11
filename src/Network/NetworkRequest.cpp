#include "NetworkRequest.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDomDocument>

#include <XMLGenerator.h>
#include <ServiceObject.h>

NetworkRequest::NetworkRequest()
{

    url = "https://lite.realtime.nationalrail.co.uk/OpenLDBWS/ldb7.asmx";
}

NetworkRequest::~NetworkRequest()
{
    delete mgr;
}


void NetworkRequest::sendXYZRequest(QString operation,int numRows, QString CRS, QString filterCRS, QString filterType, QString timeOffset, QString timeWindow){

    QByteArray xml=generator.createOperationXML(operation,numRows, CRS, filterCRS, filterType, timeOffset, timeWindow);

    mgr = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    request.setUrl(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    request.setSslConfiguration(config);

    mgr->post(request, xml);
    connect(mgr, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(XYZReplyFinished(QNetworkReply*)));
    eventLoop.exec();
}

void NetworkRequest::XYZReplyFinished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        xmlDoc.setContent(reply->readAll(),0,0,0,0);
        delete reply;
        qDebug() << xmlDoc.toString(1);
        eventLoop.exit(0);
        processXYZReply();
    }
    else {
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        eventLoop.exit(0);
    }

}

void NetworkRequest::processXYZReply(){

    m_services.clear();

    QDomNodeList messages = xmlDoc.elementsByTagName("lt3:nrccMessages");

    if(messages.length() !=0){
        for (int i = 0; i < messages.size(); i++) {
            QDomNode messageNode = messages.item(i);
            QDomElement element = messageNode.firstChildElement("lt:message");
            MessageObject message(element.text());
            m_messages.append(message);
        }
    }else{
        m_messages.clear();
        MessageObject message("This station has no messages");
        m_messages.append(message);
    }

    QDomNodeList services = xmlDoc.elementsByTagName("lt3:service");
    for (int i = 0; i < services.size(); i++) {
        QDomNode service = services.item(i);

        QDomElement origin = service.firstChildElement("lt3:origin");
        QDomNode location = origin.firstChild();
        QDomElement locationName = location.firstChildElement("lt2:locationName");
        QDomElement locationCRS =  location.firstChildElement("lt2:crs");

        QDomElement destination= service.firstChildElement("lt3:destination");
        QDomNode destinationNode = destination.firstChild();
        QDomElement destinationName = destinationNode.firstChildElement("lt2:locationName");
        QDomElement destinationCRS =  destinationNode.firstChildElement("lt2:crs");

        //Changes between sta and std but actually both can be used.
        QDomElement std = service.firstChildElement("lt3:std");
        QDomElement etd = service.firstChildElement("lt3:etd");

        QDomElement sta = service.firstChildElement("lt3:sta");
        QDomElement eta = service.firstChildElement("lt3:eta");

        QDomElement platform = service.firstChildElement("lt3:platform");
        QDomElement trainOperator = service.firstChildElement("lt3:operator");
        QDomElement operatorCode = service.firstChildElement("lt3:operatorCode");
        QDomElement serviceID = service.firstChildElement("lt3:serviceID");

        ServiceObject object(locationName.text(),locationCRS.text(), destinationName.text(),destinationCRS.text(), std.text(),etd.text(),sta.text(),eta.text(),platform.text(),trainOperator.text(),operatorCode.text(),serviceID.text());

        m_services.append(object);
    }

    emit messagesProcessed(m_messages);
    emit dataProcessed(m_services);
}

QList<ServiceObject> NetworkRequest::getServicesList(){
    return m_services;
}

void NetworkRequest::sendServiceIDRequest(QString serviceID){

    m_previousCallingPoints.clear();
    m_subsequentCallingPoints.clear();

    QByteArray xml = generator.createServiceDetailXML(serviceID);

    mgr = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    request.setUrl(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    request.setSslConfiguration(config);

    mgr->post(request, xml);
    connect(mgr, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ServiceIDReplyFinished(QNetworkReply*)));
    eventLoop.exec();
}

void NetworkRequest::ServiceIDReplyFinished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        xmlDoc.setContent(reply->readAll(),0,0,0,0);
        delete reply;
        //qDebug() << xmlDoc.toString(1);
        eventLoop.exit(0);
        processServiceIDReply();
    }
    else {
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        eventLoop.exit(0);
    }

}

void NetworkRequest::processServiceIDReply(){

    QDomNodeList previousCallingPoints = xmlDoc.elementsByTagName("lt2:previousCallingPoints");
    QDomNodeList subsequentCallingPoints = xmlDoc.elementsByTagName("lt2:subsequentCallingPoints");

    QDomNodeList previousCallingPointsList = previousCallingPoints.at(0).firstChild().childNodes();
    QDomNodeList subsequentCallingPointsList = subsequentCallingPoints.at(0).firstChild().childNodes();

    if(previousCallingPointsList.length() !=0){
        for (int i = 0; i < previousCallingPoints.size(); i++) {
            QDomNode callingpoint = previousCallingPointsList.at(i);

            QDomElement locationName = callingpoint.firstChildElement("lt:locationName");
            QDomElement crs = callingpoint.firstChildElement("lt:crs");
            QDomElement st = callingpoint.firstChildElement("lt:st");
            QDomElement at = callingpoint.firstChildElement("lt:at");

            CallingPointObject cp(locationName.text(),crs.text(),st.text(),at.text());
            m_previousCallingPoints.append(cp);
        }
    }

    if(subsequentCallingPointsList.length() !=0){
        for (int i = 0; i < subsequentCallingPointsList.size(); i++) {
            QDomNode callingpoint = subsequentCallingPointsList.at(i);

            QDomElement locationName = callingpoint.firstChildElement("lt:locationName");
            QDomElement crs = callingpoint.firstChildElement("lt:crs");
            QDomElement st = callingpoint.firstChildElement("lt:st");
            QDomElement at = callingpoint.firstChildElement("lt:at");

            CallingPointObject cp(locationName.text(),crs.text(),st.text(),at.text());
            m_subsequentCallingPoints.append(cp);

        }
    }

    emit previousCallingPointsProcessed(m_previousCallingPoints);
    emit subsequentCallingPointsProcessed(m_subsequentCallingPoints);

}





