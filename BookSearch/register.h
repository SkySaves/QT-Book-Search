#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <QtSql>
#include "loginform.h"
#include "qdialog.h"
#include "mydb.h"

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QDialog
{
    Q_OBJECT

public:
    RegisterForm(QDialog *parent = nullptr);
    ~RegisterForm();

private slots:
    void on_btnRegister_clicked();

private:
    Ui::RegisterForm *ui;

    QSqlDatabase db;
};

#endif // REGISTERFORM_H
