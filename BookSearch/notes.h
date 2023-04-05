#ifndef NOTES_H
#define NOTES_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class notes;
}

class notes : public QDialog
{
    Q_OBJECT

public:
    explicit notes(QWidget *parent = nullptr);
    ~notes();

private slots:
    void on_saveNoteBttn_clicked();

    void on_newNoteBttn_clicked();


    void on_exitButton_clicked();

private:
    Ui::notes *ui;
    QString ongoingFile = "";
};

#endif // NOTES_H
