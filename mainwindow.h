#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "vpropertiesmodel.h"
#include <QMainWindow>
#include <QSqlRelationalTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VPropertiesModel *propertyModel;
    QSqlRelationalTableModel *relationModel;
};
#endif // MAINWINDOW_H
