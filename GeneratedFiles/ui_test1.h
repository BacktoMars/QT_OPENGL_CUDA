/********************************************************************************
** Form generated from reading UI file 'test1.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST1_H
#define UI_TEST1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test1Class)
    {
        if (test1Class->objectName().isEmpty())
            test1Class->setObjectName(QStringLiteral("test1Class"));
        test1Class->resize(600, 400);
        menuBar = new QMenuBar(test1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        test1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        test1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(test1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        test1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(test1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        test1Class->setStatusBar(statusBar);

        retranslateUi(test1Class);

        QMetaObject::connectSlotsByName(test1Class);
    } // setupUi

    void retranslateUi(QMainWindow *test1Class)
    {
        test1Class->setWindowTitle(QApplication::translate("test1Class", "test1", 0));
    } // retranslateUi

};

namespace Ui {
    class test1Class: public Ui_test1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST1_H
