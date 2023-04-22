#include "notes.h"
#include "ui_notes.h"

notes::notes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notes)
{
    ui->setupUi(this);
    //removes the X button at the top of the window.
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    // Disconnect any existing connections
    disconnect(ui->exitButton, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->exitButton, &QPushButton::clicked, this, &notes::on_exitButton_clicked);

    disconnect(ui->newNoteBttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->newNoteBttn, &QPushButton::clicked, this, &notes::on_newNoteBttn_clicked);

    disconnect(ui->saveNoteBttn, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->saveNoteBttn, &QPushButton::clicked, this, &notes::on_saveNoteBttn_clicked);

}

notes::~notes()
{
    delete ui;
}

void notes::on_saveNoteBttn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", QString(), "Text Files (*.txt)");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Error with saving file: " + file.errorString());
        return;
    } else
    {

    }
    ongoingFile = fileName;
    QTextStream out(&file);
    QString text = ui->noteEdit->toPlainText();
    out << text;
    file.close();
}


void notes::on_newNoteBttn_clicked()
{
    //clears the notepad
    ongoingFile.clear();
    ui->noteEdit->setText(QString());
}


void notes::on_exitButton_clicked()
{
    //checks if the note has been saved before exiting
    if (!ongoingFile.isEmpty())
    {
        close();
    }
    else
    {   //if the file has not been saved, it will warn the user before exiting and give them an option of saving or not.
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Warning", "You are exiting without saving. Would you like to save before exiting?");
        if (confirmation == QMessageBox::Yes)
        {
            on_saveNoteBttn_clicked();
            close();
        }
        else
        {
            close();
        }
    }
}

