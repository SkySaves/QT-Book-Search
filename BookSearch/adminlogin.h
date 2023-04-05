#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QMainWindow>
#include "adminwindow.h"

namespace Ui {
class adminlogin;
}

class adminlogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminlogin(QWidget *parent = nullptr);
    ~adminlogin();

private slots:
    void on_adminloginBttn_clicked();

private:
    Ui::adminlogin *ui;
    adminwindow *Adminwindow;
};

#endif // ADMINLOGIN_H
