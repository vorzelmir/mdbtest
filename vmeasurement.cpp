#include "vmeasurement.h"
#include "vdatabasemanager.h"
#include <QSqlQuery>

const auto CREATE_MEAS = QLatin1String (R"(
    create table measurement_group(id integer primary key autoincrement,
                                pattern varchar (50),
                                name varchar (15),
                                full_name varchar (50),
                                description text,
                                image blob,
                                group_name varchar (50),
                                unique (pattern, name),
                                foreign key (pattern) references pattern_system (id),
                                foreign key (group_name) references measurement_group (id)))");

const auto INSERT_MEAS = QLatin1String (R"(
    insert into measurement(pattern, name, full_name, description, image, group_name),
    values (?, ?, ?, ?, ?, ?))");

const auto SELECT_MEAS = QLatin1String(R"(
    select * from measurement )");

const auto MEAS_TABLE = QStringLiteral ("measurement");

VMEAS::VMEAS(QSqlDatabase &db) noexcept:
    mDatabase(db)
{

}

void VMEAS::Init() const
{
    QSqlQuery query (mDatabase);
    query.prepare(CREATE_MEAS);
    VDatabaseManager::Warning(query);
    query.exec();
}

void VMEAS::AddMeasurement(MEAS &meas) const
{
    QSqlQuery query (mDatabase);
    query.prepare(INSERT_MEAS);
    query.addBindValue(meas.Pattern());
    query.addBindValue(meas.Name());
    query.addBindValue(meas.FullName());
    query.addBindValue(meas.Description());
    query.addBindValue(meas.Image());
    query.addBindValue(meas.Group());
    meas.SetId(query.lastInsertId().toInt());
    VDatabaseManager::Warning(query);
    query.exec();
}

vectorMEAS VMEAS::MeaasurementBuffer() const
{
    QSqlQuery query (SELECT_MEAS, mDatabase);
    query.exec();
    VDatabaseManager::Warning(query);
    vectorMEAS list (new std::vector<std::unique_ptr<MEAS>>);
    while (query.next())
    {
        std::unique_ptr<MEAS> meas (new MEAS());
        meas->SetPattern(query.value(1).toString());
        meas->SetName(query.value(2).toString());
        meas->SetFullname(query.value(3).toString());
        meas->SetDescription(query.value(4).toString());
        meas->SetImage(query.value(5).toByteArray());
        meas->SetGroup(query.value(6).toString());
        meas->SetId(query.lastInsertId().toInt());
        list->push_back(move(meas));
    }
    return list;
}
