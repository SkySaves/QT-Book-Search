#include "loginform.h"
#include "mainwindow.h"
#include "about.h"
#include <QApplication>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include "adminwindow.h"
#include "adminlogin.h"




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
    //sets a style called Fusion that allows the GUI to stay consistent across platforms (mac and windows)
    QApplication::setStyle("Fusion");
    //Enables the QT Menubar on MacOS. Due to a bug, this isn't enabled by default on Mac.
    #ifdef Q_OS_MACOS
        QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    #endif

    // Create a splash screen
       QSplashScreen splash;

    // Load the pixmap from a relative path
       QDir projectDir = QDir(QCoreApplication::applicationDirPath());
       QPixmap pixmap(projectDir.filePath(":/images/clueless.png"));

    // Calculate the new splash screen size
         QRect totalScreenGeometry;
         QList<QScreen *> screens = QApplication::screens();
         for (QScreen *screen : screens) {
             totalScreenGeometry = totalScreenGeometry.united(screen->geometry());
         }

         int newSplashWidth = static_cast<int>(totalScreenGeometry.width() * 0.15);
         int newSplashHeight = static_cast<int>(totalScreenGeometry.height() * 0.15);

    // Resize the splash screen pixmap
        QPixmap resizedPixmap = pixmap.scaled(newSplashWidth, newSplashHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        splash.setPixmap(resizedPixmap);
        splash.show();


    // Get primary and secondary screens
        QScreen *primaryScreen = QApplication::primaryScreen();
        QScreen *secondaryScreen = screens.size() > 1 ? screens[1] : nullptr;

    // Move splash screen to secondary screen if available
        if (secondaryScreen) {
            QRect secondaryScreenGeometry = secondaryScreen->geometry();
             splash.move(secondaryScreenGeometry.center());
             }

    // Display a message in the center of the splash screen
        splash.showMessage("Now loading CIS 227 Bookstore", Qt::AlignCenter | Qt::AlignBottom, Qt::red);

    // Configure the logging framework
    QLoggingCategory logCategory("BookSearch");
        qInstallMessageHandler(messageHandler);

        LoginForm w;

    // Get the geometry of the primary screen
        QRect screenGeometry = primaryScreen->geometry();

    // Move the main form to the center of the primary screen
        w.move(screenGeometry.center() - w.rect().center());

    // Pause the application for 3000 milliseconds (3 seconds)
        QTimer::singleShot(3000, &splash, [&]() {
            splash.close();
            w.show();
    });

    return a.exec();
}
