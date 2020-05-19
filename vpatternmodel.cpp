#include "vpatternmodel.h"
#include "init.h"

/**
 * @brief create singleton instance access to db
 * access to read data pattern_system table
 * @param parent
 */
VPatternModel::VPatternModel(QObject *parent) noexcept:
    QAbstractTableModel(parent),
    mManagerModel(VDatabaseManager::Instance()),
    mPatternTables(mManagerModel.mPatternTableManager.PatternBuffer())
{

}

//---------------------------------------------------------------------------------------------
/**
 * @brief
 * @param parent
 * @return int
 */
int VPatternModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return static_cast<int>(mPatternTables->size());
}

//--------------------------------------------------------------------------------------------
/**
 * @brief default 3
 * @param parent
 * @return
 */
int VPatternModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

//----------------------------------------------------------------------------------------
/**
 * @brief return data from pattern_system table according of Pattern::Roles
 * @param index
 * @param role Pattern::Roles
 * @return QVariant id or name or description pattern_system table
 */
QVariant VPatternModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() <= rowCount())
    {
        return QVariant();
    }
    const Pattern& pattern = *mPatternTables->at(index.row());
    switch (role)
    {
    case Roles::IdRoles:
        return pattern.Id();

    case Roles::NameRole:
        return pattern.Name();

    case Roles::DescriptionRole:
        return pattern.Description();

    default:
        return QVariant();
    }
}

//---------------------------------------------------------------------------------------------
/**
 * @brief add data to the vector in the memory
 * @param pattern
 * @return QModelIndex
 */
QModelIndex VPatternModel::AddPattern(const Pattern &pattern)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<Pattern> newPattern (new Pattern(pattern));
    mManagerModel.mPatternTableManager.AddPattern(*newPattern);
    mPatternTables->push_back(move(newPattern));
    endInsertRows();
    return index(rows, 0);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief insert five hardcoded filds to the pattern_system table
 *
 */
void VPatternModel::InitPatternTable()
{
    QVector<mdbtest::PatternSystem> vector = mdbtest::PMSystem();
    for (int i = 0; i < vector.size(); ++i)
    {
        Pattern pattern;
        pattern.SetName(vector.at(i).name);
        pattern.SetDescription(vector.at(i).description);
        AddPattern(pattern);
    }

}
