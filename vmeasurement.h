#ifndef VMEASUREMENT_H
#define VMEASUREMENT_H
#include <QString>
#include <QSqlDatabase>
#include <memory>
#include <vector>

namespace mdbtest
{
    struct MEAS;
    class VMEAS;
}

struct MEAS
{
    constexpr int Id () const { return mId;}
    QString Pattern () const { return mPattern; }
    QString Name () const { return mName; }
    QString FullName () const { return mFullName; }
    QString Description () const { return mDescription; }
    QByteArray Image () const { return mImage; }
    QString Group () const { return mGroup; }

    void SetId (const int i) { mId = i; }
    void SetPattern (const QString &p) { mPattern = p;}
    void SetName (const QString &n) { mName = n; }
    void SetFullname (const QString &f) { mFullName = f; }
    void SetDescription (const QString &d) { mDescription = d; }
    void SetImage (const QByteArray &a) { mImage = a; }
    void SetGroup (const QString &g) { mGroup = g; }
private:
    int mId;
    QString mPattern;
    QString mName;
    QString mFullName;
    QString mDescription;
    QByteArray mImage;
    QString mGroup;
};

using vectorMEAS = std::unique_ptr<std::vector<std::unique_ptr<MEAS>>>;

class VMEAS
{
public:
    explicit VMEAS(QSqlDatabase &db) noexcept;
    void Init () const;
    void AddMeasurement (MEAS &meas) const;
    vectorMEAS MeaasurementBuffer () const;
private:
    QSqlDatabase &mDatabase;
};

#endif // VMEASUREMENT_H
