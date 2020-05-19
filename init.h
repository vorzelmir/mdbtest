/**
 * @brief helper functions to insert data to the database to test it
 *
 */
#ifndef INIT_H
#define INIT_H
#include <QMap>
#include <QString>
#include <QVector>

namespace mdbtest
{
struct PatternSystem
{
    QString name;
    QString description;
//    PatternSystem () = default;
//    PatternSystem (QString n, QString d):
//        name(n), description(d) {}
};

struct GroupName
{
    QString name;
    QString pattern;

};

/**
 * @brief insert data to the pattern_system table
 * @return QVector<PatternSystem>
 */
QVector <PatternSystem> PMSystem();

/**
 * @brief insert data to the group_names table
 * @return QVector<GroupName>
 */
QVector <GroupName> GroupNames ();

}
#endif // INIT_H
