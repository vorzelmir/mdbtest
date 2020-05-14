#ifndef VPROPERTIESMODEL_H
#define VPROPERTIESMODEL_H
#include "vdatabasemanager.h"
#include "vproperties.h"

#include <QAbstractListModel>
#include <QVariant>
#include <memory>

namespace mdbtest
{
    class VPropertiesModel;
}

class VPropertiesModel : public QAbstractListModel
{
    enum Roles { IdRole=Qt::UserRole+1, VersionRole=1};
    Q_OBJECT
public:
    VPropertiesModel(QObject* parent=nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

    void AddProperty();
private:
    VDatabaseManager& mManager;
    vectorProperties mPropertiesTables;
};

#endif // VPROPERTIESMODEL_H
