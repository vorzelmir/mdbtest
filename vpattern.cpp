#include "vpattern.h"
#include "vdatabasemanager.h"

const auto CREATE_PATTERN = QLatin1String (R"(
    create table pattern_system(id integer primary key autoincrement,
                                name varchar (50),
                                description text,
                                unique (name)))");

const auto INSERT_PATTERN = QLatin1String (R"(
    insert into pattern_system(name, description) values (?, ?))");

const auto SELECT_PATTERN = QLatin1String(R"(
    select * from pattern_system )");

const auto PATTERN_TABLE = QStringLiteral ("pattern_system");

//------------------------------------------------------------------------------------------
VPattern::VPattern(QSqlDatabase &db):
    mDatabase(db)
{

}

//--------------------------------------------------------------------------------------------
/**
 * @brief create pattern_system table
 */
void VPattern::Init() const
{
    if (!mDatabase.tables().contains(PATTERN_TABLE))
    {
        QSqlQuery query (CREATE_PATTERN);
        VDatabaseManager::Warning(query);
        query.exec();
    }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief add values to the pattern_system table
 * @param pattern
 */
void VPattern::AddPattern(Pattern &pattern) const
{
    QSqlQuery query (mDatabase);
    query.prepare(INSERT_PATTERN);

    query.addBindValue(pattern.Name());
    query.addBindValue(pattern.Description());
    pattern.SetId(query.lastInsertId().toInt());
    VDatabaseManager::Warning(query);
    query.exec();
}

//----------------------------------------------------------------------------------------------
/**
 * @brief buffer of accessing to the database through the vector in the memory
 * @return vectorPatterns
 */
vectorPatterns VPattern::PatternBuffer() const
{
    QSqlQuery query (SELECT_PATTERN, mDatabase);
    query.exec();
    VDatabaseManager::Warning(query);
    vectorPatterns list (new std::vector<std::unique_ptr<Pattern>>);
    while (query.next())
    {
        std::unique_ptr<Pattern> pattern (new Pattern());
        pattern->SetName(query.value(1).toString());
        pattern->SetDescription(query.value(2).toString());
        pattern->SetId(query.lastInsertId().toInt());
        list->push_back(move(pattern));
    }
    return list;
}
