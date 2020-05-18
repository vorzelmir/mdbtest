#ifndef VPROPERTIES_H
#define VPROPERTIES_H

#include <QtSql/QSqlDatabase>
#include <QMetaType>
#include <memory>

namespace mdbtest
{
    struct Properties;
    class VProperties;
}
#define FORMAT_VERSION(major, minor, patch) ((major<<16)|(minor<<8)|(patch))
struct Properties
{
    Properties ():
        mId(),
        mVersion(Version())
    {

    }
    constexpr int Id () const { return mId;}
    constexpr int Version () const
    {
        const int value = FORMAT_VERSION(0, 0, 1);
        return value;
    }

    constexpr void SetId (int const& id)  { mId = id;}
    constexpr void SetVersion (int const& version) { mVersion = version;}
private:
    int mId, mVersion;
};

using vectorProperties = std::unique_ptr<std::vector<std::unique_ptr<Properties>>>;
class VProperties
{
public:
    explicit VProperties(QSqlDatabase& db) noexcept;
    void Init() const;
    void AddProperties(const Properties &table) const;
    vectorProperties PropertiesBuffer() const;
private:
    QSqlDatabase& mDatabase;
};

Q_DECLARE_METATYPE (Properties)
#endif // VPROPERTIES_H
