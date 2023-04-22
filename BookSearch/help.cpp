#include "help.h"
#include "ui_help.h"
#include <qsysinfo>
#include <QRegularExpression>
#include <QStringList>

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)

{
    //removes the X button at the top of the window.
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QSysInfo *sysInfo = new QSysInfo();
    ui->setupUi(this);
    ui->tableHardware->verticalHeader()->hide();
    ui->tableHardware->horizontalHeader()->hide();
    ui->tableHardware->setItem(0,0, new QTableWidgetItem("Property"));
    ui->tableHardware->setItem(0,1, new QTableWidgetItem("Value"));

    QString buildApi = sysInfo->buildAbi();
    QRegularExpression rx("[-]");
    QStringList list = buildApi.split(rx);

    ui->tableHardware->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableHardware->setItem(1,0, new QTableWidgetItem("Architecture"));
    ui->tableHardware->setItem(1,1, new QTableWidgetItem(list[0]));

    ui->tableHardware->setRowCount(3);
    ui->tableHardware->setItem(2,0, new QTableWidgetItem("Endianness"));
    ui->tableHardware->setItem(2,1, new QTableWidgetItem(list[1]));

    ui->tableHardware->setRowCount(4);
    ui->tableHardware->setItem(3,0, new QTableWidgetItem("Product Version"));
    ui->tableHardware->setItem(3,1, new QTableWidgetItem(sysInfo->productVersion()));

    ui->tableHardware->setRowCount(5);
    ui->tableHardware->setItem(4,0, new QTableWidgetItem("Product Name"));
    ui->tableHardware->setItem(4,1, new QTableWidgetItem(sysInfo->prettyProductName()));


}

help::~help()
{
    delete ui;
}
