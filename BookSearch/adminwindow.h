#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
namespace Ui {
class adminwindow;
}

class adminwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();

private slots:
    void on_adminAddUserbttn_clicked();

    void on_changePassBttn_clicked();

    void on_importBttn_clicked();

    void on_addAdminbttn_clicked();


    void on_backbttn_clicked();

private:
    Ui::adminwindow *ui;
};

#endif // ADMINWINDOW_H
