/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QLineEdit *InputLine;
    QPushButton *OrderButton;
    QPushButton *RandomButton;
    QLabel *label;
    QPushButton *QuitButton;
    QLineEdit *OutputLine;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *QuestionLine;
    QLineEdit *Fileline;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(70, 40, 118, 23));
        progressBar->setValue(24);
        InputLine = new QLineEdit(centralwidget);
        InputLine->setObjectName(QString::fromUtf8("InputLine"));
        InputLine->setGeometry(QRect(250, 270, 311, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(20);
        InputLine->setFont(font);
        OrderButton = new QPushButton(centralwidget);
        OrderButton->setObjectName(QString::fromUtf8("OrderButton"));
        OrderButton->setGeometry(QRect(110, 460, 93, 29));
        RandomButton = new QPushButton(centralwidget);
        RandomButton->setObjectName(QString::fromUtf8("RandomButton"));
        RandomButton->setGeometry(QRect(280, 460, 93, 29));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 260, 111, 61));
        QFont font1;
        font1.setPointSize(26);
        label->setFont(font1);
        QuitButton = new QPushButton(centralwidget);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));
        QuitButton->setGeometry(QRect(440, 460, 93, 29));
        OutputLine = new QLineEdit(centralwidget);
        OutputLine->setObjectName(QString::fromUtf8("OutputLine"));
        OutputLine->setGeometry(QRect(250, 350, 311, 61));
        OutputLine->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 180, 111, 61));
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 350, 111, 61));
        label_3->setFont(font1);
        QuestionLine = new QLineEdit(centralwidget);
        QuestionLine->setObjectName(QString::fromUtf8("QuestionLine"));
        QuestionLine->setGeometry(QRect(250, 180, 311, 61));
        QuestionLine->setFont(font);
        Fileline = new QLineEdit(centralwidget);
        Fileline->setObjectName(QString::fromUtf8("Fileline"));
        Fileline->setGeometry(QRect(260, 40, 113, 24));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(480, 40, 69, 20));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(550, 40, 113, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        InputLine->setText(QString());
        OrderButton->setText(QCoreApplication::translate("MainWindow", "Order", nullptr));
        RandomButton->setText(QCoreApplication::translate("MainWindow", "Random", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245", nullptr));
        QuitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\227\256\351\242\230", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\255\224\346\241\210", nullptr));
        QuestionLine->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\207\206\347\241\256\347\216\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
