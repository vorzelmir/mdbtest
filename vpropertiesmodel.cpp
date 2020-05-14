#include "vpropertiesmodel.h"

VPropertiesModel::VPropertiesModel(QObject *parent):
    QAbstractListModel(parent),
    mManager(VDatabaseManager::Instance()),
    mPropertiesTables(mManager.mPropertiesTableManager.PropertiesBuffer())
{

}

int VPropertiesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(mPropertiesTables->size());
}

QVariant VPropertiesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && index.row() < rowCount())
    {
        return QVariant();
    }
    const Properties& table = *mPropertiesTables->at(static_cast<unsigned int>(index.row()));
    switch (role)
    {
    case Roles::IdRole:
        return table.Id();

    case Roles::VersionRole:
        return table.Version();

    default:
        return QVariant();
    }
}

void VPropertiesModel::AddProperty()
{
    const Properties &property{};
    int rowIndex = rowCount();
    if (rowIndex == 0)
    {
        beginInsertRows(QModelIndex(), rowIndex, rowIndex);//to insert one row
        std::unique_ptr<Properties> newProperties(new Properties(property));
        //access to the VPropertiesTableData::AddProperties()
        mManager.mPropertiesTableManager.AddProperties (*newProperties);
        mPropertiesTables->push_back(std::move(newProperties));//change the owner of properties
        endInsertRows();
    }
}
