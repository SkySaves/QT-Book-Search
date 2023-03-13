#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QLoggingCategory>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFile m_logFile;

private slots:

    void on_btnRegister_clicked();

    void on_btnSearch_clicked();
};
#endif // MAINWINDOW_H
