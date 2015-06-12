#ifndef MESSAGEOBJECT_H
#define MESSAGEOBJECT_H

#include <QObject>

class MessageObject
{

public:
    explicit MessageObject(QString);
    QString getMessage();

private:
    QString m_message;
};

#endif // MESSAGEOBJECT_H
