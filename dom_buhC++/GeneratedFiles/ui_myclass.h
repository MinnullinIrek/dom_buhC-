/********************************************************************************
** Form generated from reading UI file 'myclass.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLASS_H
#define UI_MYCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyClassClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyClassClass)
    {
        if (MyClassClass->objectName().isEmpty())
            MyClassClass->setObjectName(QStringLiteral("MyClassClass"));
        MyClassClass->resize(600, 400);
        centralWidget = new QWidget(MyClassClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 256, 192));
        MyClassClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyClassClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        MyClassClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyClassClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyClassClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyClassClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyClassClass->setStatusBar(statusBar);

        retranslateUi(MyClassClass);

        QMetaObject::connectSlotsByName(MyClassClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyClassClass)
    {
        MyClassClass->setWindowTitle(QApplication::translate("MyClassClass", "MyClass", 0));
    } // retranslateUi

};

namespace Ui {
    class MyClassClass: public Ui_MyClassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLASS_H
