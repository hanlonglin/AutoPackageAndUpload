/********************************************************************************
** Form generated from reading UI file 'ftp_upload.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTP_UPLOAD_H
#define UI_FTP_UPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ftp_uploadClass
{
public:
    QAction *actionConfig;
    QAction *actionShowLog;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGroupBox *groupBox_3;
    QTextEdit *textEditTest;
    QPushButton *pushButtonUpload;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonChoose;
    QLineEdit *lineEditPath;
    QLabel *label;
    QGroupBox *groupBox_4;
    QLabel *labelFtpConfig;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ftp_uploadClass)
    {
        if (ftp_uploadClass->objectName().isEmpty())
            ftp_uploadClass->setObjectName(QStringLiteral("ftp_uploadClass"));
        ftp_uploadClass->resize(560, 550);
        actionConfig = new QAction(ftp_uploadClass);
        actionConfig->setObjectName(QStringLiteral("actionConfig"));
        actionShowLog = new QAction(ftp_uploadClass);
        actionShowLog->setObjectName(QStringLiteral("actionShowLog"));
        centralWidget = new QWidget(ftp_uploadClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(0, 0, 561, 511));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 120, 541, 371));
        textEditTest = new QTextEdit(groupBox_3);
        textEditTest->setObjectName(QStringLiteral("textEditTest"));
        textEditTest->setGeometry(QRect(10, 120, 521, 251));
        pushButtonUpload = new QPushButton(groupBox_3);
        pushButtonUpload->setObjectName(QStringLiteral("pushButtonUpload"));
        pushButtonUpload->setGeometry(QRect(220, 70, 75, 23));
        horizontalLayoutWidget = new QWidget(groupBox_3);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 521, 41));
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

        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 100, 54, 12));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 541, 91));
        labelFtpConfig = new QLabel(groupBox_4);
        labelFtpConfig->setObjectName(QStringLiteral("labelFtpConfig"));
        labelFtpConfig->setGeometry(QRect(20, 19, 511, 61));
        ftp_uploadClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ftp_uploadClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 560, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        ftp_uploadClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ftp_uploadClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ftp_uploadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ftp_uploadClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ftp_uploadClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionConfig);
        menu->addAction(actionShowLog);

        retranslateUi(ftp_uploadClass);

        QMetaObject::connectSlotsByName(ftp_uploadClass);
    } // setupUi

    void retranslateUi(QMainWindow *ftp_uploadClass)
    {
        ftp_uploadClass->setWindowTitle(QApplication::translate("ftp_uploadClass", "ftp_upload", 0));
        actionConfig->setText(QApplication::translate("ftp_uploadClass", "\351\205\215\347\275\256ftp", 0));
        actionShowLog->setText(QApplication::translate("ftp_uploadClass", "\346\237\245\347\234\213\346\227\245\345\277\227", 0));
        groupBox->setTitle(QString());
        groupBox_3->setTitle(QApplication::translate("ftp_uploadClass", "\344\270\212\344\274\240\346\226\207\344\273\266\357\274\232", 0));
        pushButtonUpload->setText(QApplication::translate("ftp_uploadClass", "\345\274\200\345\247\213\344\270\212\344\274\240", 0));
        pushButtonChoose->setText(QApplication::translate("ftp_uploadClass", "\351\200\211\346\213\251json\346\226\207\344\273\266", 0));
        label->setText(QApplication::translate("ftp_uploadClass", "\344\270\212\344\274\240\347\273\223\346\236\234\357\274\232", 0));
        groupBox_4->setTitle(QApplication::translate("ftp_uploadClass", "ftp\351\205\215\347\275\256\344\277\241\346\201\257", 0));
        labelFtpConfig->setText(QString());
        menu->setTitle(QApplication::translate("ftp_uploadClass", "\347\274\226\350\276\221", 0));
    } // retranslateUi

};

namespace Ui {
    class ftp_uploadClass: public Ui_ftp_uploadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTP_UPLOAD_H
