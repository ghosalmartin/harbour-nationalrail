#include "MessageObject.h"

MessageObject::MessageObject(QString message)
{
    m_message = message;
}

QString MessageObject::getMessage(){
    return m_message;
}
