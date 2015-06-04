#ifndef QMLACCESSLAYER_H
#define QMLACCESSLAYER_H

#include <QObject>
#include <XMLGenerator.h>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDomDocument>
#include <QQuickView>
#include <ServiceModel.h>

class NetworkRequest : public QObject
{

Q_OBJECT

public:
    NetworkRequest();
    Q_INVOKABLE void sendXYZRequest(QString operation,int numRows, QString CRS, QString filterCRS, QString filterType, QString timeOffset, QString timeWindow);
    void processXYZReply();
    ServiceModel getModel();
    QDomDocument xmlDoc;

public slots:
    void XYZReplyFinished(QNetworkReply *reply);
    QList<ServiceObject> getServicesList();

signals:
     void dataProcessed(QList<ServiceObject> services);

private:
     QNetworkAccessManager *mgr;
     QEventLoop eventLoop;
     QList<ServiceObject> m_services;
};

#endif // QMLACCESSLAYER_H
