#ifndef STATIONSFILTERMODEL_H
#define STATIONSFILTERMODEL_H

#include <QSortFilterProxyModel>

#include "StationsModel.h"

class StationsFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit StationsFilterModel();

    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
    QString filter() const;
    void setFilter(const QString &filter);

private:
    StationsModel *model;

signals:
    void filterChanged();

};

#endif // STATIONSFILTERMODEL_H
