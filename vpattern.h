#ifndef VPATTERN_H
#define VPATTERN_H

#include <QString>
#include <QVariant>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <memory>
#include <vector>

namespace mdbtest
{
    struct Pattern;
    class VPattern;
}

struct Pattern
{
    explicit Pattern ():
        mPatternId(),
        mPatternName(),
        mPatternDescription()
    {

    }
    explicit Pattern (QString &n, QString &d):
        mPatternId(),
        mPatternName(n),
        mPatternDescription(d)
    {

    }
    constexpr int Id () const { return mPatternId; }
    QString Name () const { return  mPatternName; }
    QString Description () const { return mPatternDescription; }

    constexpr void SetId (const int id) { mPatternId = id; };
    void SetName (const QString name) { mPatternName = name; }
    void SetDescription (const QString descp) { mPatternDescription = descp; }
private:
    int mPatternId;
    QString mPatternName;
    QString mPatternDescription;
};

using vectorPatterns = std::unique_ptr<std::vector<std::unique_ptr<Pattern>>>;
class VPattern
{
public:
    explicit VPattern (QSqlDatabase &db);
    void Init () const;
    void AddPattern (Pattern &pattern) const;
    vectorPatterns PatternBuffer () const;
private:
    QSqlDatabase& mDatabase;
};
Q_DECLARE_METATYPE (Pattern)
#endif // VPATTERN_H
