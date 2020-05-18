#ifndef VPATTERNMODEL_H
#define VPATTERNMODEL_H
#include <QAbstractTableModel>

#include "vdatabasemanager.h"
#include "vpattern.h"

namespace mdbtest
{
    class VPatternModel;
}

class VPatternModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VPatternModel(QObject *parent=nullptr) noexcept;
    enum Roles {IdRoles = Qt::UserRole + 1,
                NameRole = Qt::UserRole + 2,
                DescriptionRole = Qt::UserRole + 3};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QModelIndex AddPattern(const Pattern& pattern);
    void InitPatternTable();
private:
    VDatabaseManager &mManagerModel;
    vectorPatterns mPatternTables;
};

#endif // VPATTERNMODEL_H
