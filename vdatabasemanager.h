#ifndef VDATABASEMANAGER_H
#define VDATABASEMANAGER_H

#include "vproperties.h"
#include "vpattern.h"
#include "vgroup.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <memory>

namespace mdbtest
{
    class VDatabaseManager;
}

class VDatabaseManager
{
public:
    static VDatabaseManager& Instance();
    ~VDatabaseManager();
    static void Warning(const QSqlQuery &query);
private:
    VDatabaseManager();
    std::unique_ptr<QSqlDatabase> mManager;
public:
    const VProperties mPropertiesTableManager;
    const VPattern mPatternTableManager;
    const VGroup mGroupTableMananer;
};

#endif // VDATABASEMANAGER_H
