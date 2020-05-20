#include "vgroup.h"
#include <QSqlQuery>
#include "vdatabasemanager.h"

const auto CREATE_GROUP = QLatin1String (R"(
    create table measurement_group(id integer primary key autoincrement,
                                name varchar (15),
                                pattern varchar (50),
                                unique (name, pattern),
                                foreign key (pattern) references pattern_system (id)))");

const auto INSERT_GROUP = QLatin1String (R"(
    insert into measurement_group(name, pattern) values (?, ?))");

const auto SELECT_GROUP = QLatin1String(R"(
    select * from measurement_group )");

const auto GROUP_TABLE = QStringLiteral ("measurement_group");

VGroup::VGroup(QSqlDatabase &db):
    mDatabase(db)
{

}

void VGroup::Init() const
{
    if (!mDatabase.tables().contains(GROUP_TABLE))
    {
        QSqlQuery query (mDatabase);
        query.prepare(CREATE_GROUP);
        VDatabaseManager::Warning(query);
        query.exec();
    }
}

void VGroup::AddGroup(Group &group) const
{
    QSqlQuery query (mDatabase);
    query.prepare(INSERT_GROUP);
    query.addBindValue(group.Name());
    query.addBindValue(group.Pattern());
    group.SetId(query.lastInsertId().toInt());
    VDatabaseManager::Warning(query);
    query.exec();
}

vectorGroup VGroup::GroupBuffer() const
{
    QSqlQuery query (SELECT_GROUP, mDatabase);
    query.exec();
    VDatabaseManager::Warning(query);
    vectorGroup list (new std::vector<std::unique_ptr<Group>>);
    while (query.next())
    {
        std::unique_ptr<Group> group (new Group());
        group->SetName(query.value(1).toString());
        group->SetPattern(query.value(2).toString());
        group->SetId(query.lastInsertId().toInt());
        list->push_back(move(group));
    }
    return list;
}
