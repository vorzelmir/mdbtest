/**
 * @brief temprorary file with helper functions to insert data to the database to test it
 */
#ifndef INIT_H
#define INIT_H
#include <QString>
#include <QVector>

namespace mdbtest
{
struct PatternSystem
{
    QString name;
    QString description;
};

struct GroupName
{
    QString name;
    QString pattern;
};

/**
 * @brief insert default data to the pattern_system table
 * @return QVector<PatternSystem>
 */
QVector <PatternSystem> PMSystem();

/**
 * @brief insert default data to the measurement_group table
 * @return QVector<GroupName>
 */
QVector <GroupName> GroupNames ();

}
#endif // INIT_H
