#include "register.h"
#include "ui_register.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "mydb.h"


RegisterForm::RegisterForm(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
    // Disconnect any existing connections
    disconnect(ui->btnRegister, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterForm::on_btnRegister_clicked);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::on_btnRegister_clicked()
{
    // Get the username and password input from the QLineEdit objects
    QString username = ui->lineUsername->text();
    QString password = ui->linePassword->text();

    // Check if the username or password fields are empty
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please enter a username and password.");
        return;
    }

    // Check if the username already exists in the database
    QSqlDatabase db = MyDB::getInstance()->getDBInstance();
    QSqlQuery query(db);
    query.prepare("SELECT UserID FROM customerLogin WHERE Username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to query the database: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        // Username already exists in the database
        QMessageBox::warning(this, "Registration Error", "Username already exists. Please choose a different one.");
        return;
    }

    // Username is unique, so insert the new user into the database
    query.prepare("INSERT INTO customerLogin (Username, Password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to insert into the database: " + query.lastError().text());
        return;
    }

    // Show a success message and close the form
    QMessageBox::information(this, "Registration Successful", "Account created successfully.");
    LoginForm* loginForm = new LoginForm();
    loginForm->show();
    this->close();
}
