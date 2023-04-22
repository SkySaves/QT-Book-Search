#include "adminwindow.h"
#include "loginform.h"
#include "ui_adminwindow.h"
#include "mydb.h"
#include <QMessageBox>

adminwindow::adminwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);

    // Disconnect any existing connections
    disconnect(ui->addAdminbttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->addAdminbttn, &QPushButton::clicked, this, &adminwindow::on_addAdminbttn_clicked);

    disconnect(ui->adminAddUserbttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->adminAddUserbttn, &QPushButton::clicked, this, &adminwindow::on_adminAddUserbttn_clicked);

    disconnect(ui->changePassBttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->changePassBttn, &QPushButton::clicked, this, &adminwindow::on_changePassBttn_clicked);

    disconnect(ui->importBttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->importBttn, &QPushButton::clicked, this, &adminwindow::on_importBttn_clicked);

}




adminwindow::~adminwindow()
{
    delete ui;
}

void adminwindow::on_adminAddUserbttn_clicked()
{
    QString newUsername = ui->lineEdit_adminCUser->text();
    QString newPass = ui->lineEdit_adminCPass->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(QString("INSERT INTO customerLogin (Username, Password) VALUES (:username, :pass)"));
    query.bindValue(":username", newUsername);
    query.bindValue(":pass", newPass);

    if(query.exec())
    {
        QMessageBox::information(this, "Success", "User added successfully");
        //clears the text boxes
        ui->lineEdit_adminCUser->setText(QString());
        ui->lineEdit_adminCPass->setText(QString());
    } else
    {
        QMessageBox::warning(this, "Error", "Unable to add user");
    }
}

void adminwindow::on_changePassBttn_clicked()
{
    QString currentUsername = ui->lineEdit_changeUser->text();
    QString newPassword = ui->lineEdit_changePass->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(QString("UPDATE customerLogin SET Password = :newPass WHERE Username = :username"));
    query.bindValue(":username", currentUsername);
    query.bindValue(":newPass", newPassword);

    if(query.exec())
    {
        QMessageBox::information(this, "Success", "Password for " + currentUsername + " has been changed!");
        //clears the textbox
        ui->lineEdit_changeUser->setText(QString());
        ui->lineEdit_changePass->setText(QString());
    } else
    {
        QMessageBox::warning(this, "Error", "Unable to change password");
    }
}

void adminwindow::on_importBttn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Import file");

       if (!filename.isEmpty())
       {
           //creates a folder called adminfiles so it can import the files in there
           QString filePath = QCoreApplication::applicationDirPath() + "/adminfiles/";
           QString destinationFile = filePath + QFileInfo(filename).fileName();
           //checks if the file was copied correctly in the destination file (adminfiles)
           if (QFile::copy(filename, destinationFile))
           {
               QMessageBox::information(this, "Success", "File was imported");
           }
           else
           {
               QMessageBox::warning(this, "Warning", "File failed to imported");
           }
       }
}

void adminwindow::on_addAdminbttn_clicked()
{
    QString newAdminUser = ui->lineEdit_newAdminUser->text();
    QString newAdminPass = ui->lineEdit_newAdminPass->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(QString("INSERT INTO adminLogin (Username, Password) VALUES (:username, :pass)"));
    query.bindValue(":username", newAdminUser);
    query.bindValue(":pass", newAdminPass);

    if(query.exec())
    {
        QMessageBox::information(this, "Success", "Admin successfully added");
        //clears the text boxes
        ui->lineEdit_newAdminUser->setText(QString());
        ui->lineEdit_newAdminPass->setText(QString());
    } else
    {
        QMessageBox::warning(this, "Error", "Unable to create admin");
    }
}

void adminwindow::on_backbttn_clicked()
{
    LoginForm *loginForm = new LoginForm;
    loginForm->show();
    close();
}

