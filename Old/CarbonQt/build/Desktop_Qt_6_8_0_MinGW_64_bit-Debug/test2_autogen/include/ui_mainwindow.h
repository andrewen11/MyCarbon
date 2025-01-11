/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *homeTab;
    QLabel *electrictyLabel;
    QLineEdit *electricityInput;
    QLabel *gasLabel;
    QLineEdit *gasInput;
    QLabel *waterLabel;
    QLineEdit *waterInput;
    QLabel *woodLabel;
    QLineEdit *woodInput;
    QWidget *foodTab;
    QLabel *beefLabel;
    QLineEdit *beefInput;
    QLabel *eggLabel;
    QLineEdit *eggInput;
    QLabel *lambLabel;
    QLineEdit *lambInput;
    QLabel *porkLabel;
    QLineEdit *porkInput;
    QWidget *humanTab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(640, 480);
        tabWidget = new QTabWidget(MainWindow);
        tabWidget->setObjectName("tabWidget");
        homeTab = new QWidget();
        homeTab->setObjectName("homeTab");
        electrictyLabel = new QLabel(homeTab);
        electrictyLabel->setObjectName("electrictyLabel");
        electrictyLabel->setGeometry(QRect(20, 20, 200, 30));
        electricityInput = new QLineEdit(homeTab);
        electricityInput->setObjectName("electricityInput");
        electricityInput->setGeometry(QRect(250, 20, 100, 30));
        gasLabel = new QLabel(homeTab);
        gasLabel->setObjectName("gasLabel");
        gasLabel->setGeometry(QRect(20, 60, 200, 30));
        gasInput = new QLineEdit(homeTab);
        gasInput->setObjectName("gasInput");
        gasInput->setGeometry(QRect(250, 60, 100, 30));
        waterLabel = new QLabel(homeTab);
        waterLabel->setObjectName("waterLabel");
        waterLabel->setGeometry(QRect(20, 100, 200, 30));
        waterInput = new QLineEdit(homeTab);
        waterInput->setObjectName("waterInput");
        waterInput->setGeometry(QRect(250, 100, 100, 30));
        woodLabel = new QLabel(homeTab);
        woodLabel->setObjectName("woodLabel");
        woodLabel->setGeometry(QRect(20, 140, 200, 30));
        woodInput = new QLineEdit(homeTab);
        woodInput->setObjectName("woodInput");
        woodInput->setGeometry(QRect(250, 140, 100, 30));
        tabWidget->addTab(homeTab, QString());
        foodTab = new QWidget();
        foodTab->setObjectName("foodTab");
        beefLabel = new QLabel(foodTab);
        beefLabel->setObjectName("beefLabel");
        beefLabel->setGeometry(QRect(20, 20, 200, 30));
        beefInput = new QLineEdit(foodTab);
        beefInput->setObjectName("beefInput");
        beefInput->setGeometry(QRect(250, 20, 100, 30));
        eggLabel = new QLabel(foodTab);
        eggLabel->setObjectName("eggLabel");
        eggLabel->setGeometry(QRect(20, 60, 200, 30));
        eggInput = new QLineEdit(foodTab);
        eggInput->setObjectName("eggInput");
        eggInput->setGeometry(QRect(250, 60, 100, 30));
        lambLabel = new QLabel(foodTab);
        lambLabel->setObjectName("lambLabel");
        lambLabel->setGeometry(QRect(20, 100, 200, 30));
        lambInput = new QLineEdit(foodTab);
        lambInput->setObjectName("lambInput");
        lambInput->setGeometry(QRect(250, 100, 100, 30));
        porkLabel = new QLabel(foodTab);
        porkLabel->setObjectName("porkLabel");
        porkLabel->setGeometry(QRect(20, 140, 200, 30));
        porkInput = new QLineEdit(foodTab);
        porkInput->setObjectName("porkInput");
        porkInput->setGeometry(QRect(250, 140, 100, 30));
        tabWidget->addTab(foodTab, QString());
        humanTab = new QWidget();
        humanTab->setObjectName("humanTab");
        tabWidget->addTab(humanTab, QString());
        MainWindow->setCentralWidget(tabWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"          background-color: #000000;  \n"
"          color: white;  ", nullptr));
        tabWidget->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"           QTabWidget::pane { border: 0; }\n"
"           QTabBar::tab {\n"
"               background-color: #ffffff;  /* Dark background for tab */\n"
"               color: black;  /* Tab text color (black) */\n"
"               padding: 10px;\n"
"           }\n"
"           QTabBar::tab:selected {\n"
"               background-color: #3C3939;  /* Slightly lighter background for selected tab */\n"
"               color: white;  /* Text color for selected tab (white) */\n"
"           }\n"
"           QTabBar::tab:hover {\n"
"               background-color: #f2f2f2;  /* Hover effect for tab */\n"
"           }\n"
"           /* Keep content inside tabs white */\n"
"           QTabWidget {\n"
"               background-color: #ffffff;\n"
"               color: black;  /* White text color inside tabs */\n"
"           }\n"
"       ", nullptr));
        electrictyLabel->setText(QCoreApplication::translate("MainWindow", "Electricity consumption", nullptr));
        gasLabel->setText(QCoreApplication::translate("MainWindow", "Gas consumption", nullptr));
        waterLabel->setText(QCoreApplication::translate("MainWindow", "Water consumption", nullptr));
        woodLabel->setText(QCoreApplication::translate("MainWindow", "Wood consumption", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(homeTab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        beefLabel->setText(QCoreApplication::translate("MainWindow", "Beef consumption", nullptr));
        eggLabel->setText(QCoreApplication::translate("MainWindow", "Egg consumption", nullptr));
        lambLabel->setText(QCoreApplication::translate("MainWindow", "Lamb consumption", nullptr));
        porkLabel->setText(QCoreApplication::translate("MainWindow", "Pork consumption", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(foodTab), QCoreApplication::translate("MainWindow", "Food", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(humanTab), QCoreApplication::translate("MainWindow", "Human", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
