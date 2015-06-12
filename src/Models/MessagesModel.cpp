#include "MessagesModel.h"

MessagesModel::MessagesModel() : QAbstractListModel(), m_networkRequest(0)
{
    _roles[messageRole] = "message";
}

int MessagesModel::rowCount(const QModelIndex &) const
{
    return _data.size();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > _data.size()) return QVariant();
    MessageObject messageObject = _data.at(row);
    switch (role)
    {
    case messageRole: return messageObject.getMessage();
    default: return QVariant();
    }
}

void MessagesModel::populateModel(QList<MessageObject> messages){

    beginResetModel();

    _data.clear();

    _data = messages;

    endResetModel();
}

void MessagesModel::setSource(NetworkRequest *source){
    if (m_networkRequest != source) {
        if (m_networkRequest) {
            disconnect(m_networkRequest, SIGNAL(messagesProcessed(QList<MessageObject>)), this, SLOT(populateModel(QList<MessageObject>)));
        }
        m_networkRequest = source;
        if (m_networkRequest) {
            connect(m_networkRequest, SIGNAL(messagesProcessed(QList<MessageObject>)), this, SLOT(populateModel(QList<MessageObject>)));
        }
        emit sourceChanged();
    }
}
