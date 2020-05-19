#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    propertyModel(nullptr),
    patternModel(nullptr),
    groupModel(nullptr),
    relationModel(nullptr)
{
    ui->setupUi(this);
    propertyModel = new VPropertiesModel(this);
    patternModel = new VPatternModel(this);
    groupModel = new VGroupModel(this);

    propertyModel->AddProperty();
    patternModel->InitPatternTable();
    groupModel->InitGroupTable();

    relationModel = new QSqlRelationalTableModel(ui->databaseTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

