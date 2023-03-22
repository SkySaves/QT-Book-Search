#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginForm; }
QT_END_NAMESPACE

class loginForm : public QMainWindow
{
    Q_OBJECT

public:
    loginForm(QWidget *parent = nullptr);
    ~loginForm();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::loginForm *ui;
    MainWindow *mainwindow;
};
#endif // LOGINFORM_H
