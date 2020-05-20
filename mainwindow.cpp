#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlError>
#include <QMessageBox>
#include <QSqlRelationalDelegate>

const auto PATTERN_TABLE = QStringLiteral ("pattern_system");
const auto GROUP_TABLE = QStringLiteral ("measurement_group");
const auto MEAS_TABLE = QStringLiteral ("measurement");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    propertyModel(nullptr),
    patternModel(nullptr),
    groupModel(nullptr),
    measModel(nullptr),
    relationModel(nullptr)
{
    ui->setupUi(this);
    propertyModel = new VPropertiesModel(this);
    patternModel = new VPatternModel(this);
    groupModel = new VGroupModel(this);
    measModel = new VMeasurementModel(this);

    propertyModel->AddProperty();
    patternModel->InitPatternTable();
    groupModel->InitGroupTable();
    measModel->InitMEASTable();

    relationModel = new QSqlRelationalTableModel(ui->databaseTable);
    relationModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    relationModel->setTable(MEAS_TABLE);
    int indexPattern = relationModel->fieldIndex("pattern");
    int indexGroup = relationModel->fieldIndex("group_name");

    relationModel->setRelation(indexPattern, QSqlRelation(PATTERN_TABLE, "description", "description"));
    relationModel->setRelation(indexGroup, QSqlRelation(GROUP_TABLE, "name", "name"));

    relationModel->setHeaderData(relationModel->fieldIndex("pattern"), Qt::Horizontal, QObject::tr("Pattern Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("name"), Qt::Horizontal, QObject::tr("Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("full_name"), Qt::Horizontal, QObject::tr("Full Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("description"), Qt::Horizontal, QObject::tr("Description"));
    relationModel->setHeaderData(relationModel->fieldIndex("image"), Qt::Horizontal, QObject::tr("Image"));
    relationModel->setHeaderData(relationModel->fieldIndex("group_name"), Qt::Horizontal, QObject::tr("Group Name"));

    if (!relationModel->select())
    {
        QMessageBox::critical(this, "Unable to load database",
                              "Error", relationModel->lastError().text());
        return;
    }

    ui->databaseTable->setModel(relationModel);
    ui->databaseTable->setColumnHidden(relationModel->fieldIndex("id"), true);
    ui->databaseTable->setItemDelegate(new QSqlRelationalDelegate());
    ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->databaseTable->setAutoScroll(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}

