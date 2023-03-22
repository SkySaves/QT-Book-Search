/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginForm
{
public:
    QAction *actionRegister_Account;
    QWidget *centralwidget;
    QLineEdit *txtUsername;
    QLineEdit *txtPass;
    QPushButton *btnLogin;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnLoginExit;
    QMenuBar *menubar;
    QMenu *menuRegister;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *loginForm)
    {
        if (loginForm->objectName().isEmpty())
            loginForm->setObjectName("loginForm");
        loginForm->resize(365, 277);
        actionRegister_Account = new QAction(loginForm);
        actionRegister_Account->setObjectName("actionRegister_Account");
        centralwidget = new QWidget(loginForm);
        centralwidget->setObjectName("centralwidget");
        txtUsername = new QLineEdit(centralwidget);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(120, 90, 113, 22));
        txtPass = new QLineEdit(centralwidget);
        txtPass->setObjectName("txtPass");
        txtPass->setGeometry(QRect(120, 130, 113, 22));
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(170, 210, 75, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 10, 191, 31));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 90, 61, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 130, 61, 16));
        btnLoginExit = new QPushButton(centralwidget);
        btnLoginExit->setObjectName("btnLoginExit");
        btnLoginExit->setGeometry(QRect(260, 210, 80, 24));
        loginForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(loginForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 365, 21));
        menuRegister = new QMenu(menubar);
        menuRegister->setObjectName("menuRegister");
        loginForm->setMenuBar(menubar);
        statusbar = new QStatusBar(loginForm);
        statusbar->setObjectName("statusbar");
        loginForm->setStatusBar(statusbar);

        menubar->addAction(menuRegister->menuAction());

        retranslateUi(loginForm);
        QObject::connect(btnLoginExit, &QPushButton::clicked, loginForm, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(loginForm);
    } // setupUi

    void retranslateUi(QMainWindow *loginForm)
    {
        loginForm->setWindowTitle(QCoreApplication::translate("loginForm", "Login", nullptr));
        actionRegister_Account->setText(QCoreApplication::translate("loginForm", "Register Account", nullptr));
        btnLogin->setText(QCoreApplication::translate("loginForm", "Login", nullptr));
        label->setText(QCoreApplication::translate("loginForm", "Customer Login", nullptr));
        label_2->setText(QCoreApplication::translate("loginForm", "Username:", nullptr));
        label_3->setText(QCoreApplication::translate("loginForm", "Password:", nullptr));
        btnLoginExit->setText(QCoreApplication::translate("loginForm", "Exit", nullptr));
        menuRegister->setTitle(QCoreApplication::translate("loginForm", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginForm: public Ui_loginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
