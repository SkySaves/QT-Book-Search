#include "mainwindow.h"
#include <QApplication>


void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    static QFile logFile("booksearch.log");
    if (!logFile.isOpen()) {
        logFile.open(QFile::WriteOnly | QFile::Text);
    }

    QTextStream logStream(&logFile);
    switch (type) {
    case QtDebugMsg:
        logStream << "Debug: ";
        break;
    case QtInfoMsg:
        logStream << "Info: ";
        break;
    case QtWarningMsg:
        logStream << "Warning: ";
        break;
    case QtCriticalMsg:
        logStream << "Critical: ";
        break;
    case QtFatalMsg:
        logStream << "Fatal: ";
        break;
    }

    logStream << message << Qt::endl;
    logStream.flush();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure the logging framework
    QLoggingCategory logCategory("BookSearch");
    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();
    return a.exec();
}
