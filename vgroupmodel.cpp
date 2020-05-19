#include "vgroupmodel.h"
#include "init.h"

VGroupModel::VGroupModel(QObject *parent) noexcept:
    QAbstractTableModel(parent),
    mManagerModel(VDatabaseManager::Instance()),
    mGroupTables(mManagerModel.mGroupTableManager.GroupBuffer())
{

}

//---------------------------------------------------------------------------------------------
/**
 * @brief
 * @param parent
 * @return int
 */
int VGroupModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return static_cast<int>(mGroupTables->size());
}

//--------------------------------------------------------------------------------------------
/**
 * @brief default 3
 * @param parent
 * @return
 */
int VGroupModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

//----------------------------------------------------------------------------------------
/**
 * @brief return data from measurement_group table according of Group::Roles
 * @param index
 * @param role Group::Roles
 * @return QVariant id or name or description pattern_system table
 */
QVariant VGroupModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() <= rowCount())
    {
        return QVariant();
    }
    const Group& group = *mGroupTables->at(index.row());
    switch (role)
    {
    case Roles::IdRoles:
        return group.Id();

    case Roles::NameRole:
        return group.Name();

    case Roles::PatternRole:
        return group.Pattern();

    default:
        return QVariant();
    }
}

//---------------------------------------------------------------------------------------------
/**
 * @brief add data to the vector in the memory
 * @param group
 * @return QModelIndex
 */
QModelIndex VGroupModel::AddGroup(const Group &group)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<Group> newGroup (new Group(group));
    mManagerModel.mGroupTableManager.AddGroup(*newGroup);
    mGroupTables->push_back(move(newGroup));
    endInsertRows();
    return index(rows, 0);
}

//------------------------------------------------------------------------------------------------
/**
 * @brief insert five filds to the measurement_group table
 */
void VGroupModel::InitGroupTable()
{
    QVector <mdbtest::GroupName> vector = mdbtest::GroupNames();
    for (int i = 0; i < vector.size(); ++i)
    {
        Group group;
        group.SetName(vector.at(i).name);
        group.SetPattern(vector.at(i).pattern);
        AddGroup(group);
    }
}
