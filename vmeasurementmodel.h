#ifndef VMEASUREMENTMODEL_H
#define VMEASUREMENTMODEL_H
#include "vmeasurement.h"
#include "vdatabasemanager.h"

#include <QAbstractTableModel>

namespace mdbtest
{
    class VMeasurementModel;
}
class VMeasurementModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VMeasurementModel(QObject *parent=nullptr) noexcept;
    enum Roles {IdRoles = Qt::UserRole + 1,
                PatternRole = Qt::UserRole + 2,
                NameRole = Qt::UserRole + 3,
                FullNameRole = Qt::UserRole + 4,
                DescriptionRole = Qt::UserRole + 5,
                ImageRole = Qt::UserRole + 6,
                GroupRole = Qt::UserRole + 7};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QModelIndex AddMEAS(const MEAS& meas);
    void InitMEASTable();
private:
    VDatabaseManager &mManagerModel;
    vectorMEAS mMEASTables;

    QByteArray RenderImage(const QString &path) const;
};

#endif // VMEASUREMENTMODEL_H
