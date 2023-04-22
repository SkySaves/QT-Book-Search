#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cart.h"
#include <QMainWindow>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QLoggingCategory>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QScreen>
#include <QDir>
#include <QStatusBar>
#include <QLabel>

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
    QFile *logFile;
    QLabel *bookCountLabel;
    QSqlDatabase db;
    Cart cart;
    double salesTax = 1.06;
    QVector<QStringList> selectedBooks;

private slots:

    void on_btnSearch_clicked();
    void writeToLogFile(const QString &message);
    void about();
    int getNumberOfBooks();
    void help();
    void notes();
    void on_btnAddtoCart_clicked();
    void on_btnCheckout_clicked();
    void on_btnClear_clicked();
};
#endif // MAINWINDOW_H
