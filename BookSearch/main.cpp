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

    // Create a splash screen
    QSplashScreen splash;
    QPixmap pixmap("C:/Users/sande/Documents/build-BookSearch-Desktop_Qt_6_4_2_MinGW_64_bit-Debug/clueless.png");
    splash.setPixmap(pixmap.scaled(pixmap.width() / 2, pixmap.height() / 2, Qt::KeepAspectRatio));
    splash.show();

    // Display a message in the center of the splash screen
    splash.showMessage("Now loading CIS 227 Bookstore", Qt::AlignCenter | Qt::AlignBottom, Qt::red);

    // Configure the logging framework
    QLoggingCategory logCategory("BookSearch");
    qInstallMessageHandler(messageHandler);

    MainWindow w;

    // Get the geometry of the primary screen
    QScreen *primaryScreen = QApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    // Move the splash screen to the center of the primary screen
    splash.move(screenGeometry.center() - splash.rect().center());

    // Move the main form to the center of the primary screen
    w.move(screenGeometry.center() - w.rect().center());

    // Pause the application for 3000 milliseconds (3 seconds)
    QTimer::singleShot(3000, &splash, [&]() {
        splash.close();
        w.show();
    });

    return a.exec();
}

