#ifndef VGROUPMODEL_H
#define VGROUPMODEL_H

#include "vgroup.h"
#include "vdatabasemanager.h"
#include <QAbstractTableModel>

namespace mdbtest
{
    class VGroupModel;
}

class VGroupModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VGroupModel(QObject *parent=nullptr) noexcept;
    enum Roles {IdRoles = Qt::UserRole + 1,
                NameRole = Qt::UserRole + 2,
                PatternRole = Qt::UserRole + 3};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QModelIndex AddGroup(const Group& pattern);
    void InitGroupTable();
private:
    VDatabaseManager &mManagerModel;
    vectorGroup mGroupTables;
};

#endif // VGROUPMODEL_H
