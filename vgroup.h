#ifndef VGROUP_H
#define VGROUP_H
#include <QString>
#include <QSqlDatabase>
#include <memory>
#include <vector>

namespace mdbtest
{
    struct Group;
    class VGroup;
}

struct Group
{
    explicit Group () = default;
    explicit Group (QString &n, QString &p):
        mId(),
        mName(n),
        mPattern(p)
    {

    }
    constexpr int Id () const { return mId; }
    QString Name () const { return mName; }
    QString Pattern () const { return mPattern; }

    void SetId (const int i) { mId = i;}
    void SetName (const QString &n) { mName = n; }
    void SetPattern (const QString &p) { mPattern = p; }
private:
    int mId;
    QString mName;
    QString mPattern;
};

using vectorGroup = std::unique_ptr<std::vector<std::unique_ptr<Group>>>;

class VGroup
{
public:
    explicit VGroup(QSqlDatabase &db);
    void Init () const;
    void AddGroup (Group &group) const;
    vectorGroup GroupBuffer () const;
private:
    QSqlDatabase &mDatabase;
};

#endif // VGROUP_H
