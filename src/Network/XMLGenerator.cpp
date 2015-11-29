#include "XMLGenerator.h"
#include <QDebug>
#include <QXmlStreamWriter>
#include <QBuffer>

QByteArray XMLGenerator::createOperationXML(QString operation,int numRows, QString CRS, QString filterCRS, QString filterType, QString timeOffset, QString timeWindow){

    QString key = "8650ba70-f8e8-4c44-af6f-49b1a9cc697c";

    QByteArray ba;
    QBuffer buffer( &ba );
    buffer.open(QIODevice::ReadWrite);

    QXmlStreamWriter writer(&buffer);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0");
    writer.writeStartElement("SOAP-ENV:Envelope");
    writer.writeNamespace("http://schemas.xmlsoap.org/soap/envelope/", "SOAP-ENV");
    writer.writeNamespace("http://thalesgroup.com/RTTI/2015-05-14/ldb/","ns1");
    writer.writeNamespace("http://thalesgroup.com/RTTI/2010-11-01/ldb/commontypes","ns2");

    writer.writeStartElement("SOAP-ENV:Header");
    writer.writeStartElement("ns2:AccessToken");
    writer.writeTextElement("ns2:TokenValue",key);


    //ENDS TOKEN VALUE
    writer.writeEndElement();
    //ENDS ACCESS TOKEN
    writer.writeEndElement();


    writer.writeStartElement("SOAP-ENV:Body");

    //Request needs to be tacked onto the end
    writer.writeStartElement("ns1:"+operation+"Request");

    writer.writeTextElement("ns1:numRows",QString::number(numRows));
    writer.writeTextElement("ns1:crs",CRS);

    if(!filterCRS.isEmpty()){
    writer.writeTextElement("ns1:filterCrs",filterCRS);}

    if(!filterType.isEmpty()){
    writer.writeTextElement("ns1:filterType",filterType);}

    if(!timeOffset.isEmpty()){
    writer.writeTextElement("ns1:timeOffset",timeOffset);}

    if(!timeWindow.isEmpty()){
    writer.writeTextElement("ns1:timeWindow",timeWindow);}

    //ENDS BODY
    writer.writeEndElement();



    //ENDS DOCUMENT
    writer.writeEndDocument();

    return ba;
}

QByteArray XMLGenerator::createServiceDetailXML(QString serviceID){

    QString key = "8650ba70-f8e8-4c44-af6f-49b1a9cc697c";

    QByteArray ba;
    QBuffer buffer( &ba );
    buffer.open(QIODevice::ReadWrite);

    QXmlStreamWriter writer(&buffer);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0");
    writer.writeStartElement("SOAP-ENV:Envelope");
    writer.writeNamespace("http://schemas.xmlsoap.org/soap/envelope/", "SOAP-ENV");
    writer.writeNamespace("http://thalesgroup.com/RTTI/2015-05-14/ldb/","ns1");
    writer.writeNamespace("http://thalesgroup.com/RTTI/2010-11-01/ldb/commontypes","ns2");

    writer.writeStartElement("SOAP-ENV:Header");
    writer.writeStartElement("ns2:AccessToken");
    writer.writeTextElement("ns2:TokenValue",key);


    //ENDS TOKEN VALUE
    writer.writeEndElement();
    //ENDS ACCESS TOKEN
    writer.writeEndElement();

    writer.writeStartElement("SOAP-ENV:Body");

    //Request needs to be tacked onto the end
    writer.writeStartElement("ns1:GetServiceDetailsRequest");

    writer.writeTextElement("ns1:serviceID",serviceID);

    //ENDS BODY
    writer.writeEndElement();


    //ENDS DOCUMENT
    writer.writeEndDocument();

    return ba;
}
