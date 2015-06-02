#ifndef REQUEST_H
#define REQUEST_H

#include <QString>

class XMLGenerator
{

public:
    QByteArray createOperationXML(QString operation, int numRows, QString CRS, QString filterCRS, QString filterType, QString timeOffset, QString timeWindow);
    QByteArray createServiceDetailXML(QString serviceID);
};

#endif // REQUEST_H
