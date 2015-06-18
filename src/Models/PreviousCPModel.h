#ifndef PREVIOUSCPMODEL_H
#define PREVIOUSCPMODEL_H

#include <QAbstractListModel>
#include <CallingPointObject.h>
#include <NetworkRequest.h>

class PreviousCPModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(NetworkRequest * source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool ready READ getReady WRITE setReady NOTIFY readyChanged)
public:
    PreviousCPModel();

    enum Roles {
        locationNameRole = Qt::UserRole,
        crsRole = Qt::UserRole+1,
        scheduledTimeRole = Qt::UserRole +2,
        actualTimeRole = Qt::UserRole +3,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void appendRow(CallingPointObject callingPoint);

    NetworkRequest *getSource () const { return m_networkRequest; }
    void setSource(NetworkRequest *source);

    bool getReady() const {return m_ready;}
    void setReady(bool ready);

signals:
    void sourceChanged();
    void readyChanged();
public slots:
    void populateModel(QList<CallingPointObject> callingpoints);
private:
    QList<CallingPointObject> data_;
    QHash<int, QByteArray> roles_;
    NetworkRequest *m_networkRequest;
    bool m_ready;

};

#endif // CALLINGPOINTSMODEL_H


