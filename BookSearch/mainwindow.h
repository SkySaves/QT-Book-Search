#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:

    //void on_btnRegister_clicked();
    void on_btnSearch_clicked();
    void writeToLogFile(const QString &message);
    void about();
    int getNumberOfBooks();
    void help();
    void notes();
};
#endif // MAINWINDOW_H
