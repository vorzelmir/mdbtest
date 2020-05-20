#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlError>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QDataWidgetMapper>

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

    //init all the tables
    propertyModel->AddProperty();
    patternModel->InitPatternTable();
    groupModel->InitGroupTable();
    measModel->InitMEASTable();

    //add general model to set the data
    relationModel = new QSqlRelationalTableModel(ui->databaseTable);
    relationModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //in the view will be show measurement table
    relationModel->setTable(MEAS_TABLE);
    //indexes of foreign keys
    int indexPattern = relationModel->fieldIndex("pattern");
    int indexGroup = relationModel->fieldIndex("group_name");

    //create relation to measurement_group and pattern_system tables
    relationModel->setRelation(indexPattern, QSqlRelation(PATTERN_TABLE, "description", "description"));
    relationModel->setRelation(indexGroup, QSqlRelation(GROUP_TABLE, "name", "name"));

    relationModel->setHeaderData(indexPattern, Qt::Horizontal, QObject::tr("Pattern Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("name"), Qt::Horizontal, QObject::tr("Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("full_name"), Qt::Horizontal, QObject::tr("Full Name"));
    relationModel->setHeaderData(relationModel->fieldIndex("description"), Qt::Horizontal, QObject::tr("Description"));
    relationModel->setHeaderData(relationModel->fieldIndex("image"), Qt::Horizontal, QObject::tr("Image"));
    relationModel->setHeaderData(indexGroup, Qt::Horizontal, QObject::tr("Group Name"));

    if (!relationModel->select())
    {
        QMessageBox::critical(this, "Unable to load database",
                              "Error", relationModel->lastError().text());
        return;
    }

    ui->databaseTable->setModel(relationModel);

    //create comboboxes of foreigner keys inside of ui->databaseTable
    ui->databaseTable->setItemDelegate(new QSqlRelationalDelegate());

    ui->databaseTable->setColumnHidden(relationModel->fieldIndex("id"), true);
    ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->databaseTable->setAutoScroll(true);

    //two comboboxes with relation to the filds in the ui->databaseTable
    ui->patternBox->setModel(relationModel->relationModel(indexPattern));
    ui->patternBox->setModelColumn(relationModel->relationModel(indexPattern)->fieldIndex("description"));
    ui->groupnameBox->setModel(relationModel->relationModel(indexGroup));
    ui->groupnameBox->setModelColumn(relationModel->relationModel(indexGroup)->fieldIndex("name"));

    //mapping between ui->databaseTable and ui->patternBox and ui->groupnameBox
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(relationModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->patternBox, indexPattern);
    mapper->addMapping(ui->groupnameBox, indexGroup);

    connect(ui->databaseTable->selectionModel(), &QItemSelectionModel::currentRowChanged,
            mapper, &QDataWidgetMapper::setCurrentModelIndex);
}


MainWindow::~MainWindow()
{
    delete ui;
}

