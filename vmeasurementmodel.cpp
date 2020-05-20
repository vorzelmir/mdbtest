#include "vmeasurementmodel.h"
#include "init.h"

#include <QBuffer>
#include <QFile>
#include <QDebug>

VMeasurementModel::VMeasurementModel(QObject *parent) noexcept:
    QAbstractTableModel(parent),
    mManagerModel(VDatabaseManager::Instance()),
    mMEASTables(mManagerModel.mMEASTableManager.MeaasurementBuffer())
{

}

//---------------------------------------------------------------------------------------------
/**
 * @brief
 * @param parent
 * @return int
 */
int VMeasurementModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return static_cast<int>(mMEASTables->size());
}

//--------------------------------------------------------------------------------------------
/**
 * @brief default 3
 * @param parent
 * @return
 */
int VMeasurementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

//----------------------------------------------------------------------------------------
/**
 * @brief return data from measurement table according of VMeasurement::Roles
 * @param index
 * @param role VMeasurement::Roles
 * @return QVariant id or name or description pattern_system table
 */
QVariant VMeasurementModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() <= rowCount())
    {
        return QVariant();
    }
    const MEAS& meas = *mMEASTables->at(index.row());
    switch (role)
    {
    case Roles::IdRoles:
        return meas.Id();

    case Roles::PatternRole:
        return meas.Pattern();

    case Roles::NameRole:
        return meas.Name();

    case Roles::FullNameRole:
        return meas.FullName();

    case Roles::DescriptionRole:
        return meas.Description();

    case Roles::ImageRole:
        return meas.Image();

    case Roles::GroupRole:
        return meas.Group();

    default:
        return QVariant();
    }
}

//---------------------------------------------------------------------------------------------
/**
 * @brief add data to the vector in the memory
 * @param meas
 * @return QModelIndex
 */
QModelIndex VMeasurementModel::AddMEAS(const MEAS &meas)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<MEAS> newMEAS (new MEAS(meas));
    mManagerModel.mMEASTableManager.AddMeasurement(*newMEAS);
    mMEASTables->push_back(move(newMEAS));
    endInsertRows();
    return index(rows, 0);
}

//-------------------------------------------------------------------------------------
/**
 * @brief init (fill) the measurement table with the default data
 */
void VMeasurementModel::InitMEASTable()
{
    QVector <mdbtest::Measurement> vector = mdbtest::Measurements();
    for (int i = 0; i < vector.size(); ++i)
    {
        MEAS meas;
        meas.SetPattern(vector.at(i).pattern);
        meas.SetName(vector.at(i).name);
        meas.SetFullname(vector.at(i).fullName);
        meas.SetDescription(vector.at(i).description);
        meas.SetImage(RenderImage(vector.at(i).image));
        meas.SetGroup(vector.at(i).group);
        AddMEAS(meas);
    }
}

//---------------------------------------------------------------------------------------
/**
 * @brief convert QString file path of an image file to the QByteArray
 * @param path
 * @return QByteArray
 */
QByteArray VMeasurementModel::RenderImage(const QString &path) const
{
    QFile file {path};
    not file.open(QIODevice::ReadOnly) ? qDebug() << "File does not exist": qDebug() << " file: " << path;
    QByteArray byteArray = file.readAll();
    QBuffer buffer {};
    buffer.setBuffer(&byteArray);

    Q_ASSERT (buffer.open(QIODevice::WriteOnly));
    buffer.close();

    return byteArray;
}
