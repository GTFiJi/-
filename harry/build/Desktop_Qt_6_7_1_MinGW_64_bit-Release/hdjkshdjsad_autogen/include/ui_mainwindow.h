/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Button1;
    QPushButton *Button_2;
    QLineEdit *name;
    QLineEdit *serialnumber;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Button1 = new QPushButton(centralwidget);
        Button1->setObjectName("Button1");
        Button1->setGeometry(QRect(9, 40, 81, 20));
        Button_2 = new QPushButton(centralwidget);
        Button_2->setObjectName("Button_2");
        Button_2->setGeometry(QRect(400, 40, 80, 18));
        name = new QLineEdit(centralwidget);
        name->setObjectName("name");
        name->setGeometry(QRect(12, 80, 141, 31));
        serialnumber = new QLineEdit(centralwidget);
        serialnumber->setObjectName("serialnumber");
        serialnumber->setGeometry(QRect(400, 80, 113, 31));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 121, 381, 341));
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(400, 120, 371, 341));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 321, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(400, 60, 201, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(9, 12, 41, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 12, 40, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 470, 40, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 459, 51, 41));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(99, 459, 41, 41));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(129, 459, 61, 41));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 470, 40, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Button1->setText(QCoreApplication::translate("MainWindow", "Button1", nullptr));
        Button_2->setText(QCoreApplication::translate("MainWindow", "Button2", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " \345\234\250\344\270\213\346\241\206\344\270\255\350\276\223\345\205\245\344\272\272\345\220\215/\345\234\260\345\220\215\345\220\216\346\214\211Button1\346\237\245\350\257\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\234\250\344\270\213\346\241\206\344\270\255\350\276\223\345\205\245\345\272\217\345\217\267\345\220\216\346\214\211Button2\346\237\245\350\257\242", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\255\245\351\252\2441", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\255\245\351\252\2442", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\344\272\272\345\220\215/\345\234\260\345\220\215", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\351\241\265\347\240\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\347\253\240\350\212\202", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\344\271\246\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
