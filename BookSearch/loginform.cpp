#include "loginform.h"
#include "./ui_loginform.h"
#include <QMessageBox>
#include "mydb.h"

loginForm::loginForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginForm)
{
    ui->setupUi(this);
}

loginForm::~loginForm()
{
    delete ui;
}


void loginForm::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text();
    QString pass = ui->txtPass->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance()); //singleton pattern to call DB object. This pattern limits that only one instance is made
    query.prepare(QString("SELECT UserID FROM customerLogin WHERE Username = '" +username+"' AND Password = '" +pass+"'"));

    if(query.exec())
    {
        if(query.next())
        {
             qDebug()<<"Login succesful "<<query.value(1).toString();
             hide();
             mainwindow = new class MainWindow(this);
             mainwindow->show();
        }
        else{
             qDebug()<<"Login unsuccesful";
             QMessageBox incorrectLogin;
             incorrectLogin.setText("Incorrect password or username. Try again.");
             incorrectLogin.exec();
        }
    }
    else{
        qDebug()<<"Login unsuccesful";
    }

}

