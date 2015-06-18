#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QObject>
#include <XMLGenerator.h>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDomDocument>
#include <ServiceObject.h>
#include <MessageObject.h>
#include <CallingPointObject.h>

class NetworkRequest : public QObject
{
    Q_OBJECT
public:
    NetworkRequest();
    ~NetworkRequest();
    Q_INVOKABLE void sendXYZRequest(QString operation,int numRows, QString CRS, QString filterCRS, QString filterType, QString timeOffset, QString timeWindow);
    void processXYZReply();
    Q_INVOKABLE void sendServiceIDRequest(QString serviceID);
    void processServiceIDReply();
    QDomDocument xmlDoc;


public slots:
    void XYZReplyFinished(QNetworkReply *reply);
    void ServiceIDReplyFinished(QNetworkReply *reply);
    QList<ServiceObject> getServicesList();

signals:
     void dataProcessed(QList<ServiceObject> services);
     void messagesProcessed(QList<MessageObject> messages);
     void previousCallingPointsProcessed(QList<CallingPointObject> callingpoints);
     void subsequentCallingPointsProcessed(QList<CallingPointObject> callingpoints);

private:
     QNetworkAccessManager *mgr;
     QEventLoop eventLoop;
     QList<ServiceObject> m_services;
     QList<MessageObject> m_messages;
     QList<CallingPointObject> m_previousCallingPoints;
     QList<CallingPointObject> m_subsequentCallingPoints;
     XMLGenerator generator;
     QString url;

};

#endif // NETWORKREQUEST_H
