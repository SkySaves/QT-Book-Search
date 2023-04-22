    #include "adminlogin.h"
    #include "ui_adminlogin.h"
    #include "adminwindow.h"
    #include "mydb.h"
    #include <QMessageBox>

    adminlogin::adminlogin(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::adminlogin)
    {
        ui->setupUi(this);
        // Disconnect any existing connections
        disconnect(ui->adminloginBttn, &QPushButton::clicked, nullptr, nullptr);
        connect(ui->adminloginBttn, &QPushButton::clicked, this, &adminlogin::on_adminloginBttn_clicked);
    }

    adminlogin::~adminlogin()
    {
        delete ui;
    }

    void adminlogin::on_adminloginBttn_clicked()
    {
        QString username = ui->lineEdit_adminUser->text();
        QString pass = ui->lineEdit_adminPass->text();
        QSqlQuery query(MyDB::getInstance()->getDBInstance());
        query.prepare(QString("SELECT AdminID FROM adminLogin WHERE Username = :username AND Password = :pass"));
        query.bindValue(":username", username);
        query.bindValue(":pass", pass);

        if(query.exec())
        {
            if(query.next())
            {
                qDebug() << "Admin login successful " << query.value(0).toString();
                close();
                Adminwindow = new adminwindow(this);
                Adminwindow->show();
            }
            else
            {
                qDebug() << "Admin login unsuccessful";
                QMessageBox::warning(this, "Incorrect Login", "Incorrect password or username. Try again.");
            }
        }
        else
        {
            qDebug() << "Login unsuccessful";
        }
    }
