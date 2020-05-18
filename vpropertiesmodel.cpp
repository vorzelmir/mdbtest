#include "vpropertiesmodel.h"

VPropertiesModel::VPropertiesModel(QObject *parent):
    QAbstractListModel(parent),
    mManager(VDatabaseManager::Instance()),
    mPropertiesTables(mManager.mPropertiesTableManager.PropertiesBuffer())
{

}

//------------------------------------------------------------------------------------------------
int VPropertiesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(mPropertiesTables->size());
}

//------------------------------------------------------------------------------------------------
/**
 * @brief return data from db_properties according to the Propertie::Roles
 * @param index
 * @param role
 * @return QVariant id or version
 */
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

//---------------------------------------------------------------------------------------------
/**
 * @brief add data to the vector in the memory
 */
void VPropertiesModel::AddProperty()
{
    const Properties &property{};
    int rowIndex = rowCount();
    if (rowIndex == 0)
    {
        //to insert one row
        beginInsertRows(QModelIndex(), rowIndex, rowIndex);
        std::unique_ptr<Properties> newProperties(new Properties(property));
        //access to the VPropertiesTableData::AddProperties()
        mManager.mPropertiesTableManager.AddProperties (*newProperties);
        //change the owner of properties
        mPropertiesTables->push_back(std::move(newProperties));
        endInsertRows();
    }
}
