#ifndef VPROPERTIES_H
#define VPROPERTIES_H

#include <QtSql/QSqlDatabase>
#include <QMetaType>

struct Properties
{
    constexpr int Id () const { return mId;}
    constexpr int Version () const { return mVersion;}

    constexpr void SetId (int const& id)  { mId = id;}
    constexpr void SetVersion (int const& version) { mVersion = version;}
private:
    int mId, mVersion;
};
Q_DECLARE_METATYPE(Properties)

class VProperties
{
public:
    explicit VProperties(QSqlDatabase& db) noexcept;
    void Init() const;
    void AddProperties(const Properties &table) const;
private:
    QSqlDatabase& mDatabase;
};

#endif // VPROPERTIES_H
