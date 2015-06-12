#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include <MessageObject.h>
#include <NetworkRequest.h>

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(NetworkRequest * source READ getSource WRITE setSource NOTIFY sourceChanged)
public:
    explicit MessagesModel();

    enum Roles {
            messageRole = Qt::UserRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const { return _roles; }

    NetworkRequest *getSource () const { return m_networkRequest; }
    void setSource(NetworkRequest *source);

signals:
    void sourceChanged();
public slots:
    void populateModel(QList<MessageObject> services);
private:
    QList<MessageObject> _data;
    QHash<int, QByteArray> _roles;
    NetworkRequest *m_networkRequest;
};

#endif // MESSAGEMODEL_H
