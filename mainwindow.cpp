#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    propertyModel(nullptr),
    relationModel(nullptr)
{
    ui->setupUi(this);
    propertyModel = new VPropertiesModel(this);
    propertyModel->AddProperty();
    relationModel = new QSqlRelationalTableModel(ui->databaseTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

