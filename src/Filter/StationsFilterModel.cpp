#include "StationsFilterModel.h"

StationsFilterModel::StationsFilterModel() :
    QSortFilterProxyModel()
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(StationsModel::stationRole);
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

StationsModel * StationsFilterModel::getModel(){
    return m_model;
}

void StationsFilterModel::setModel(StationsModel *model){
    if (m_model != model) {
        m_model = model;
        setSourceModel(m_model);
        emit modelChanged();
    }
}
