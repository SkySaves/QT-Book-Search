#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include <QMessageBox>
#include "help.h"
#include "notes.h"
#include "cart.h"
#include "checkout.h"


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

    // Open the database connection
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("bookstore.db");
        if (!db.open()) {
            qDebug() << "Failed to open database";
        }


    // Connect signals and slots
    connect(ui->btnSearch, SIGNAL(clicked()), this, SLOT(on_btnSearch_clicked()));
    //connect(ui->btnRegister, SIGNAL(clicked()), this, SLOT(on_btnRegister_clicked()));

    bookCountLabel = new QLabel(this); // Create a new QLabel for displaying the number of books and set its parent to the current MainWindow instance
    int numberOfBooks = getNumberOfBooks(); // Call the getNumberOfBooks() function to retrieve the number of books in the database
    bookCountLabel->setText(QStringLiteral("Number of books in the database: %1").arg(numberOfBooks)); // Set the text of the QLabel to display the number of books
    statusBar()->addWidget(bookCountLabel); // Add the QLabel to the QStatusBar of the MainWindow

}

MainWindow::~MainWindow()
{
    writeToLogFile("User exits the application");
    logFile->close();
    delete logFile;
    delete ui;
    // Close the database connection
    db.close();
}

void MainWindow::writeToLogFile(const QString &message)
{
    if (logFile->isOpen()) {
        QTextStream logStream(logFile);
        logStream << message << "\n";
        logFile->flush();
    }
}




void MainWindow::about()
{
    class about about;
    about.exec();
}


void MainWindow::help()
{
    class help help;
    help.exec();
}

void MainWindow::notes()
{
    class notes notes;
    notes.exec();
}

void MainWindow::on_btnSearch_clicked()

    {
        // Get the search criteria from the line edit boxes
        QString isbn = ui->lineISBN->text();
        QString title = ui->lineTitle->text();
        QString author = ui->lineAuthor->text();


        if (title == "Pac-Man" && isbn == "3333360" && author == "Toru Iwatani"){

        QString gamePath = "QT-pac-man.exe";
        QFileInfo gameInfo(gamePath);

        if (gameInfo.exists()) {
            // Start the QT-pac-man game
            QProcess::startDetached(gamePath);
        } else {
            // Display an error message if the game is not installed
            QMessageBox::critical(this, "Error", "QT-pac-man is not installed on this system.");
        }
        }

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


        //Keep the disconnect and reconnect or else there will be a dublicate message box that pops up.
        // Disconnect the signal and slot
        disconnect(ui->btnSearch, SIGNAL(clicked()), this, SLOT(on_btnSearch_clicked()));

        // Connect the signal and slot again
        connect(ui->btnSearch, SIGNAL(clicked()), this, SLOT(on_btnSearch_clicked()));


        int count = 0; //counts the number of books for the statusbar.
        while (sqlQuery.next()) {
            // Get the data for each row of the result
            QString isbn = sqlQuery.value("ISBN").toString();
            QString title = sqlQuery.value("Book-Title").toString();
            QString author = sqlQuery.value("Book-Author").toString();
            count++; //counts the number of books for the statusbar.

            // Add the data to a label and add the label to the layout
            QString resultString = QString("%1: %2, by %3")
                    .arg(isbn)
                    .arg(title)
                    .arg(author);
            resultsLayout->addWidget(new QLabel(resultString));

        }

        if(count == 0){
            QMessageBox::warning(this, "Invalid search", "No books found with the search perameters. Please enter again.");
        }

        // Set the search results widget as the widget for the scroll area
        ui->scrollAreaResults->setWidget(resultsWidget);
        // Displays the total amount of books in a status bar
        ui->statusbar->showMessage(QString("Total books: %1").arg(count));

    }

int MainWindow::getNumberOfBooks() {
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM books")) {
        qWarning() << "Error: Unable to execute query to get the number of books" << query.lastError();
        return 0;
    }

    int bookCount = 0;
    if (query.next()) {
        bookCount = query.value(0).toInt();
    }

    return bookCount;
}


void MainWindow::on_btnCheckout_clicked(){
    Checkout checkout(cart.get_items());

    checkout.process_order();
    QString message;

    int totalCount = cart.get_item_count();
    if (totalCount == 0){
        message = "You have not added any books to your cart.";
    }
    else {
        QString count = QString::number(totalCount);
        double totalNumber = checkout.total_price * salesTax;
        QString total = QString::number(totalNumber, 'f', 2);

        message = "You have a total of " + count + " books in your cart\nThe total for today comes out to $" + total + ".\nThank you for shopping with us today!";

    }

    QMessageBox::information(this, "Checkout", message);

    cart.clear_cart();
    int totalCartCount = cart.get_item_count();
    ui->statusbar->showMessage(QString("Total books in cart: %1.").arg(totalCartCount));
}

void MainWindow::on_btnClear_clicked(){
    // Clear inputs
    ui->lineAuthor->clear();
    ui->lineISBN->clear();
    ui->lineTitle->clear();
}

void MainWindow::on_btnAddtoCart_clicked()
{
    QString isbn = ui->lineISBN->text();
    QString title = ui->lineTitle->text();
    QString author = ui->lineAuthor->text();

    if (title.isEmpty() || isbn.isEmpty() || author.isEmpty()) {
        // No book is selected, so do nothing
        QMessageBox::warning(this, "Invalid", "When adding book to cart, please fill out title, isbn, and author");
        return;
    }

    QString query = "SELECT * FROM books WHERE ";

    query += QString("ISBN='%1' AND ").arg(isbn);
    query += "lower(`Book-Title`) LIKE :title AND ";
    query += "lower(`Book-Author`) LIKE :author";

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

    while (sqlQuery.next()) {
        // Get the data for each row of the result
        QString isbn = sqlQuery.value("ISBN").toString();
        int book_id = isbn.toInt();
        QString title = sqlQuery.value("Book-Title").toString();
        std::string book = title.toStdString();
        double price = sqlQuery.value("MSRP").toDouble();

        QString message = "You have successfully added " + title + " to your cart!";
        // Clear inputs
        ui->lineAuthor->clear();
        ui->lineISBN->clear();
        ui->lineTitle->clear();
        // Add the data to a cart
        cart.add_item(book_id, book, price);
        QMessageBox::information(this, "Added", message);

    }

    int totalCartCount = cart.get_item_count();
    ui->statusbar->showMessage(QString("Total books in cart: %1").arg(totalCartCount));
}

