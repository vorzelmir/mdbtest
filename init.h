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

struct Measurement
{
    QString pattern;
    QString name;
    QString fullName;
    QString description;
    QByteArray image;
    QString group;
};

QVector <PatternSystem> PMSystem();

QVector <GroupName> GroupNames ();

QVector <Measurement> Measurements();

}
#endif // INIT_H
