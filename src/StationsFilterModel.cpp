#include "StationsFilterModel.h"
#include <QDebug>
StationsFilterModel::StationsFilterModel() :
    QSortFilterProxyModel()
{
    model = new StationsModel();
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(StationsModel::stationRole);

    setSourceModel(model);
}

QString StationsFilterModel::filter() const
{
    return filterRegExp().pattern();
}

void StationsFilterModel::setFilter(const QString &filter)
{
    setFilterFixedString(filter);
    emit filterChanged();
}
