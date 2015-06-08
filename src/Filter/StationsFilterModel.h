#ifndef STATIONSFILTERMODEL_H
#define STATIONSFILTERMODEL_H

#include <QSortFilterProxyModel>

#include "StationsModel.h"

class StationsFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(StationsModel * model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
public:
    explicit StationsFilterModel();
    QString filter() const;
    void setFilter(const QString &filter);
    StationsModel * getModel();
    void setModel(StationsModel *model);

private:
    StationsModel *m_model;

signals:
    void filterChanged();
    void modelChanged();
};

#endif // STATIONSFILTERMODEL_H
