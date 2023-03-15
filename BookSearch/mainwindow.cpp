#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "register.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), logFile(new QFile("booksearch.log"))
{
    // Create the log file
    // This file will be created in the directory of the build path
    if (logFile->open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
        writeToLogFile("Book Search Log File\n");
    } else {
        qDebug() << "Failed to create log file";
    }

    // Set up the logging category
    QLoggingCategory logCategory("BookSearch");

    // Set up the user interface
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->btnSearch, SIGNAL(clicked()), this, SLOT(on_btnSearch_clicked()));
    connect(ui->btnRegister, SIGNAL(clicked()), this, SLOT(on_btnRegister_clicked()));
}

MainWindow::~MainWindow()
{
    writeToLogFile("User exits the application");
    logFile->close();
    delete logFile;
    delete ui;
}

void MainWindow::writeToLogFile(const QString &message)
{
    if (logFile->isOpen()) {
        QTextStream logStream(logFile);
        logStream << message << "\n";
        logFile->flush();
    }
}

void MainWindow::on_btnRegister_clicked()
{
    writeToLogFile("User logs into the application");
    Register regDialog(this); // create an instance of the new UI
    regDialog.exec(); // show the new UI as a modal dialog
}


void MainWindow::on_btnSearch_clicked()

    {
        // Get the search criteria from the line edit boxes
        QString isbn = ui->lineISBN->text();
        QString title = ui->lineTitle->text();
        QString author = ui->lineAuthor->text();

        // Construct the SQL query based on the search criteria
        QString query = "SELECT * FROM books WHERE ";
        if (!isbn.isEmpty()) {
            query += QString("ISBN='%1' AND ").arg(isbn);
        }
        if (!title.isEmpty()) {
            query += "lower(`Book-Title`) LIKE :title AND ";
        }
        if (!author.isEmpty()) {
            query += "lower(`Book-Author`) LIKE :author AND ";
        }
        // Remove the trailing "AND" if it exists
        if (query.endsWith("AND ")) {
            query = query.left(query.length() - 4);
        }

        // Open the database and execute the query
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("bookstore.db");
        if (!db.open()) {
            qDebug() << "Failed to open database";
            return;
        }

        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if (!isbn.isEmpty()) {
            sqlQuery.bindValue(":isbn", isbn);
        }
        if (!title.isEmpty()) {
            sqlQuery.bindValue(":title", QString("%%1%").arg(title.toLower()));
        }
        if (!author.isEmpty()) {
            sqlQuery.bindValue(":author", QString("%%1%").arg(author.toLower()));
        }

        if (!sqlQuery.exec()) {
            qDebug() << "Failed to execute query";
            db.close();
            return;
        }
        writeToLogFile("Successful database operation");

        // Create a widget to hold the search results
        QWidget* resultsWidget = new QWidget();
        QVBoxLayout* resultsLayout = new QVBoxLayout(resultsWidget);
        while (sqlQuery.next()) {
            // Get the data for each row of the result
            QString isbn = sqlQuery.value("ISBN").toString();
            QString title = sqlQuery.value("Book-Title").toString();
            QString author = sqlQuery.value("Book-Author").toString();

            // Add the data to a label and add the label to the layout
            QString resultString = QString("%1: %2, by %3")
                    .arg(isbn)
                    .arg(title)
                    .arg(author);
            resultsLayout->addWidget(new QLabel(resultString));

        }

        // Set the search results widget as the widget for the scroll area
        ui->scrollAreaResults->setWidget(resultsWidget);

        // Close the database
        db.close();
    }



