#include "loginform.h"
#include <QMessageBox>
#include "mydb.h"
#include "register.h"
#include "ui_loginform.h"


LoginForm::LoginForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginForm)
{

    ui->setupUi(this);
    // Disconnect any existing connections
       disconnect(ui->btnLogin, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginForm::on_btnLogin_clicked);
}


LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::adminLogin()
{
    close();
    Adminlogin = new adminlogin(this);
    Adminlogin->show();
}


void LoginForm::newRegister()
{
    close();
    registerform = new RegisterForm();
    registerform->exec();
}

void LoginForm::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text();
    QString pass = ui->txtPass->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(QString("SELECT UserID FROM customerLogin WHERE Username = :username AND Password = :pass"));
    query.bindValue(":username", username);
    query.bindValue(":pass", pass);

    if(query.exec())
    {
        if(query.next())
        {
            qDebug() << "Login successful " << query.value(0).toString();
            close();
            mainwindow = new MainWindow(this);
            mainwindow->show();
        }
        else
        {
            qDebug() << "Login unsuccessful";
            QMessageBox::warning(this, "Incorrect Login", "Incorrect password or username. Try again.");
        }
    }
    else
    {
        qDebug() << "Login unsuccessful";
    }
}

