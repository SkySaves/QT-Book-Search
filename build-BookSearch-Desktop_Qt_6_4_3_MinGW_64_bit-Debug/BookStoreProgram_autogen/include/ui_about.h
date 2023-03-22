/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_about
{
public:
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *about)
    {
        if (about->objectName().isEmpty())
            about->setObjectName("about");
        about->resize(400, 300);
        label_2 = new QLabel(about);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 321, 81));
        label_2->setWordWrap(true);
        pushButton = new QPushButton(about);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 260, 75, 24));
        label = new QLabel(about);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 81, 16));
        label_3 = new QLabel(about);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 10, 91, 16));
        label_4 = new QLabel(about);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 70, 101, 16));
        label_5 = new QLabel(about);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 50, 49, 16));
        label_6 = new QLabel(about);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 170, 121, 16));
        label_7 = new QLabel(about);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 190, 151, 16));

        retranslateUi(about);
        QObject::connect(pushButton, &QPushButton::clicked, about, qOverload<>(&QDialog::hide));

        QMetaObject::connectSlotsByName(about);
    } // setupUi

    void retranslateUi(QDialog *about)
    {
        about->setWindowTitle(QCoreApplication::translate("about", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("about", " If you have any questions or concerns please reach out to:", nullptr));
        pushButton->setText(QCoreApplication::translate("about", "Back", nullptr));
        label->setText(QCoreApplication::translate("about", "Skyler Metzger", nullptr));
        label_3->setText(QCoreApplication::translate("about", "Fernando Alvarez ", nullptr));
        label_4->setText(QCoreApplication::translate("about", "CIS227.5660.W23 ", nullptr));
        label_5->setText(QCoreApplication::translate("about", "GRCC", nullptr));
        label_6->setText(QCoreApplication::translate("about", "metzgsky@gmail.com", nullptr));
        label_7->setText(QCoreApplication::translate("about", "fernando992013@gmail.com", nullptr));
    } // retranslateUi

};

namespace Ui {
    class about: public Ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
