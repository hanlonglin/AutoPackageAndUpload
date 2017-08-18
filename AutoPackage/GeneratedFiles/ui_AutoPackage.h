/********************************************************************************
** Form generated from reading UI file 'AutoPackage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOPACKAGE_H
#define UI_AUTOPACKAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoPackageClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonChoose;
    QLineEdit *lineEditPath;
    QPushButton *pushButtonOpen;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AutoPackageClass)
    {
        if (AutoPackageClass->objectName().isEmpty())
            AutoPackageClass->setObjectName(QStringLiteral("AutoPackageClass"));
        AutoPackageClass->resize(457, 165);
        centralWidget = new QWidget(AutoPackageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 0, 411, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonChoose = new QPushButton(horizontalLayoutWidget);
        pushButtonChoose->setObjectName(QStringLiteral("pushButtonChoose"));

        horizontalLayout->addWidget(pushButtonChoose);

        lineEditPath = new QLineEdit(horizontalLayoutWidget);
        lineEditPath->setObjectName(QStringLiteral("lineEditPath"));

        horizontalLayout->addWidget(lineEditPath);

        pushButtonOpen = new QPushButton(centralWidget);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(180, 80, 75, 23));
        AutoPackageClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AutoPackageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 457, 23));
        AutoPackageClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AutoPackageClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AutoPackageClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AutoPackageClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AutoPackageClass->setStatusBar(statusBar);

        retranslateUi(AutoPackageClass);

        QMetaObject::connectSlotsByName(AutoPackageClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoPackageClass)
    {
        AutoPackageClass->setWindowTitle(QApplication::translate("AutoPackageClass", "AutoPackage", 0));
        pushButtonChoose->setText(QApplication::translate("AutoPackageClass", "\351\200\211\346\213\251json\346\226\207\344\273\266", 0));
        pushButtonOpen->setText(QApplication::translate("AutoPackageClass", "\346\211\223\345\274\200", 0));
    } // retranslateUi

};

namespace Ui {
    class AutoPackageClass: public Ui_AutoPackageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOPACKAGE_H
