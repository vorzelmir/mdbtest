#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    propertyModel(nullptr),
    patternModel(nullptr),
    relationModel(nullptr)
{
    ui->setupUi(this);
    propertyModel = new VPropertiesModel(this);
    patternModel = new VPatternModel(this);

    propertyModel->AddProperty();
    patternModel->InitPatternTable();

    relationModel = new QSqlRelationalTableModel(ui->databaseTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

