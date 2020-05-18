#include "vproperties.h"
#include <QSqlQuery>
#include <QVariant>

const auto CREATE_PROPERTIES = QLatin1String (R"(
    create table db_properties(id integer primary key autoincrement, version integer)
    )");

const auto INSERT_PROPERTIES = QLatin1String(R"(
    insert into db_properties (version) values (?)
    )");

const auto SELECT_PROPERTIES = QLatin1String(R"(
    select * from db_properties )");

const auto PROPERTIES_TABLE = QStringLiteral ("db_properties");

//---------------------------------------------------------------------------------------------
VProperties::VProperties(QSqlDatabase &db) noexcept:
    mDatabase(db)
{

}

//----------------------------------------------------------------------------------------------
/**
 * @brief create db_properties table
 */
void VProperties::Init() const
{
    if (!mDatabase.contains(PROPERTIES_TABLE))
    {
        QSqlQuery query { mDatabase};
        query.prepare(CREATE_PROPERTIES);
        query.exec();
    }
}

//-----------------------------------------------------------------------------------------------
/**
 * @brief add values to the db_properties table
 * @param table
 */
void VProperties::AddProperties(const Properties &table) const
{
    QSqlQuery query {mDatabase};
    query.prepare(INSERT_PROPERTIES);
    query.addBindValue(table.Version());
    query.exec();
}

//-----------------------------------------------------------------------------------------------
/**
 * @brief buffer to insert data to the database through vector in the memory
 * @return vectorProperties
 */
vectorProperties VProperties::PropertiesBuffer() const
{
    QSqlQuery query (SELECT_PROPERTIES, mDatabase);
    query.exec();
    vectorProperties list (new std::vector<std::unique_ptr<Properties>>);
    while (query.next())
    {
        std::unique_ptr<Properties> property (new Properties());
        property->SetId(query.value("id").toInt());
        property->SetVersion(query.value("version").toInt());
        list->push_back(std::move(property));
    }
    return list;
}

