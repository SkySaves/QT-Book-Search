#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include <QMessageBox>
#include "help.h"
#include "notes.h"
#include "cart.h"
#include "checkout.h"
#include <QTableWidget>
#include <QTableWidgetItem>



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

    // Disconnect any existing connections
    disconnect(ui->btnSearch, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::on_btnSearch_clicked);


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
    if (title == "Pac-Man" && isbn == "3333360" && author == "Toru Iwatani")
    {
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
    //enables to the ablility to select multiple rows in the table.
    ui->tableWidgetResults->setSelectionMode(QAbstractItemView::MultiSelection);
    //only allows for rows to be selected.
    ui ->tableWidgetResults->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Initialize row count
    int count = 0;

    // Set the column headers for the table widget
    ui->tableWidgetResults->setColumnCount(4);
    ui->tableWidgetResults->setHorizontalHeaderLabels(QStringList() << "ISBN" << "Title" << "Author" << "MSRP");

    // Set the number of rows in the table widget to the number of search results
    ui->tableWidgetResults->setRowCount(count);


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

    ui->tableWidgetResults->clearContents();

    // Populate the search results directly to the table widget
    while (sqlQuery.next()) {
        QString isbn = sqlQuery.value("ISBN").toString();
        QString title = sqlQuery.value("Book-Title").toString();
        QString author = sqlQuery.value("Book-Author").toString();
        QString msrp = sqlQuery.value("MSRP").toString();
        count++;

        int row = ui->tableWidgetResults->rowCount();
        ui->tableWidgetResults->insertRow(row);
        ui->tableWidgetResults->setItem(row, 0, new QTableWidgetItem(isbn));
        ui->tableWidgetResults->setItem(row, 1, new QTableWidgetItem(title));
        ui->tableWidgetResults->setItem(row, 2, new QTableWidgetItem(author));
        ui->tableWidgetResults->setItem(row, 3, new QTableWidgetItem(msrp));
        //stretches the book title
        ui->tableWidgetResults->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    }

    if (count == 0) {
        QMessageBox::warning(this, "Invalid search", "No books found with the search parameters. Please enter again.");
    }

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

void writeReceiptToFile(QVector<QStringList> selectedBooks, QString fileName) {
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (const auto& book : selectedBooks) {
            out << book.join(", ") << "\n";
        }

        file.close();
    }
}


void MainWindow::on_btnCheckout_clicked()
{
    QString message;

    int selectedCount = ui->tableWidgetResults->selectionModel()->selectedRows().count();
    if (selectedCount == 0) {
        message = "You have not selected any books to add to your cart.";
    } else {
        std::map<int, CartItem> selectedItems;
        double selectedPriceTotal = 0;
        int i = 0;
        for (const auto &index : ui->tableWidgetResults->selectionModel()->selectedRows()) {
            QString title = ui->tableWidgetResults->item(index.row(), 1)->text();
            double price = ui->tableWidgetResults->item(index.row(), 3)->text().toDouble();
            CartItem item;
            item.title = title;
            item.price = price;
            selectedItems.insert(std::make_pair(i, item));
            selectedPriceTotal += price;
            i++;
        }

        Checkout checkout(selectedItems);
        checkout.calculate_total_price();
        double totalPrice = checkout.total_price;

        QString titles;
        for (const auto& item : selectedItems) {
            titles += item.second.title + ", " + "\n";
        }
        titles.chop(2);  // remove the last comma and space

        QString count = QString::number(selectedCount);
        QString total = QString::number(totalPrice * salesTax, 'f', 2);

        message = "You have added the following " + count + " books to your cart: \n" + titles + "\nThe total for today comes out to $" + total + ".\nThank you for shopping with us today!";
        writeReceiptToFile(selectedBooks, "book_receipt.txt"); //creates a receipt
    }
    QMessageBox::information(this, "Checkout", message);

    // Clear the cart after checkout
    cart.clear_cart();
    int totalCartCount = cart.get_item_count();
    ui->statusbar->showMessage(QString("Total books in cart: %1.").arg(totalCartCount));


    // Update the table
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT title, author, price FROM books");

    // Set the number of rows and columns in the table
    ui->tableWidgetResults->setRowCount(model->rowCount());
    ui->tableWidgetResults->setColumnCount(model->columnCount());

    // Loop through each row and column and set the data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            auto item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidgetResults->setItem(row, col, item);
        }
    }

    // Clear the selection
    ui->tableWidgetResults->clearSelection();
    //Clears the selected books.
    selectedBooks.clear();

}

void MainWindow::on_btnClear_clicked(){
    // Clear inputs
    ui->lineAuthor->clear();
    ui->lineISBN->clear();
    ui->lineTitle->clear();
    //Clears the selected books for the statusbar
    selectedBooks.clear();
    //clears the selection
    ui->tableWidgetResults->clearSelection();
}

void MainWindow::on_btnAddtoCart_clicked()
{
    // Get the selected rows
    QList<QTableWidgetItem *> selectedItems = ui->tableWidgetResults->selectedItems();

    // Check if any rows are selected
    if (selectedItems.isEmpty()) {
        return;
    }

    // Iterate over the selected rows and add the information of each selected book to the QVector
    for (int i = 0; i < selectedItems.size(); i += 4) {
        QStringList book;
        book << selectedItems[i]->text() << selectedItems[i+1]->text() << selectedItems[i+2]->text();
        selectedBooks.append(book);
    }

    // Display the number of selected books in the Cart button
    ui->statusbar->showMessage(QStringLiteral("Cart (%1)").arg(selectedBooks.size()));

}


