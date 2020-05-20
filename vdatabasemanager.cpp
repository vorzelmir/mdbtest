#include "vdatabasemanager.h"
#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QSqlError>

/**
 * @brief singleton instance of class
 * @return VDatabaseManager
 */
VDatabaseManager &VDatabaseManager::Instance()
{
    static VDatabaseManager instance;
    return instance;
}

//-------------------------------------------------------------------------------------------------
VDatabaseManager::~VDatabaseManager()
{
    mManager->close();
}

//---------------------------------------------------------------------------------------------
/**
 * @brief static warning of error
 * @param query
 */
void VDatabaseManager::Warning(const QSqlQuery &query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError)
    {
        qDebug() << "Query OK:"  << query.lastQuery();
    }
    else
    {
       qWarning() << "Query warning:" << query.lastError().text();
    }
}

//-----------------------------------------------------------------------------------------------
/**
 * @brief point to enter to the database
 */
VDatabaseManager::VDatabaseManager():
    mManager (new QSqlDatabase (QSqlDatabase::addDatabase("QSQLITE"))),
    mPropertiesTableManager(*mManager),
    mPatternTableManager(*mManager),
    mGroupTableManager(*mManager),
    mMEASTableManager(*mManager)
{
    QDir dir;
    const auto dirPath = QDir::homePath() + QStringLiteral("/Valentina");
    dir.mkdir(dirPath);
    const auto filePath = dirPath + dir.filePath("/valentina.sql");
    QFile file(filePath);
    file.open(QIODevice::WriteOnly| QIODevice::ReadOnly);
    if (!file.exists())
    {
        mManager->setDatabaseName(filePath);
        qDebug() << filePath << " Doesn't exist";
    }
    else
    {
       qDebug() << filePath << " exist";
    }
    mManager->setDatabaseName(filePath);
    bool isConnected = mManager->open();
    qDebug() << "Database connection: " << (isConnected ? true: false);
    mPropertiesTableManager.Init();
    mPatternTableManager.Init();
    mGroupTableManager.Init();
    mMEASTableManager.Init();
}


