#include "vproperties.h"
#include <QSqlQuery>
#include <QVariant>

const auto CREATE_PROPERTIES = QLatin1String (R"(
    create table db_properties(id integer primary key autoincrement, version integer)
    )");

const auto INSERT_PROPERTIES = QLatin1String(R"(
    insert into db_properties (id, version(?)
    )");

VProperties::VProperties(QSqlDatabase &db) noexcept:
    mDatabase(db)
{

}

void VProperties::Init() const
{
    if (!mDatabase.contains("db_properties"))
    {
        QSqlQuery query { mDatabase};
        query.prepare(CREATE_PROPERTIES);
        query.exec();
    }
}

void VProperties::AddProperties(const Properties &table) const
{
    QSqlQuery query {mDatabase};
    query.prepare(INSERT_PROPERTIES);
    query.addBindValue(table.Version());
    query.exec();
}
