/********************************************************************************
** Form generated from reading UI file 'configFtpWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGFTPWINDOW_H
#define UI_CONFIGFTPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configFtpWindow
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEditUserName;
    QLineEdit *lineEditPasswd;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditServer;
    QLineEdit *lineEditPort;
    QPushButton *pushButtonSaveExit;
    QGroupBox *groupBox_3;
    QLineEdit *lineEditWorkDir;
    QLabel *label_5;

    void setupUi(QWidget *configFtpWindow)
    {
        if (configFtpWindow->objectName().isEmpty())
            configFtpWindow->setObjectName(QStringLiteral("configFtpWindow"));
        configFtpWindow->resize(400, 383);
        groupBox = new QGroupBox(configFtpWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 321, 121));
        lineEditUserName = new QLineEdit(groupBox);
        lineEditUserName->setObjectName(QStringLiteral("lineEditUserName"));
        lineEditUserName->setGeometry(QRect(130, 30, 171, 20));
        lineEditPasswd = new QLineEdit(groupBox);
        lineEditPasswd->setObjectName(QStringLiteral("lineEditPasswd"));
        lineEditPasswd->setGeometry(QRect(130, 80, 171, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 80, 54, 12));
        groupBox_2 = new QGroupBox(configFtpWindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 160, 321, 121));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 30, 101, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 70, 54, 12));
        lineEditServer = new QLineEdit(groupBox_2);
        lineEditServer->setObjectName(QStringLiteral("lineEditServer"));
        lineEditServer->setGeometry(QRect(130, 30, 171, 20));
        lineEditPort = new QLineEdit(groupBox_2);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));
        lineEditPort->setGeometry(QRect(130, 70, 171, 20));
        pushButtonSaveExit = new QPushButton(configFtpWindow);
        pushButtonSaveExit->setObjectName(QStringLiteral("pushButtonSaveExit"));
        pushButtonSaveExit->setGeometry(QRect(150, 350, 75, 23));
        groupBox_3 = new QGroupBox(configFtpWindow);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 280, 321, 51));
        lineEditWorkDir = new QLineEdit(groupBox_3);
        lineEditWorkDir->setObjectName(QStringLiteral("lineEditWorkDir"));
        lineEditWorkDir->setGeometry(QRect(130, 20, 171, 20));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(70, 20, 54, 12));

        retranslateUi(configFtpWindow);

        QMetaObject::connectSlotsByName(configFtpWindow);
    } // setupUi

    void retranslateUi(QWidget *configFtpWindow)
    {
        configFtpWindow->setWindowTitle(QApplication::translate("configFtpWindow", "configFtpWindow", 0));
        groupBox->setTitle(QApplication::translate("configFtpWindow", "\347\224\250\346\210\267\344\277\241\346\201\257\357\274\232", 0));
        label->setText(QApplication::translate("configFtpWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_2->setText(QApplication::translate("configFtpWindow", "\345\257\206\347\240\201\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("configFtpWindow", "\346\234\215\345\212\241\345\231\250\344\277\241\346\201\257", 0));
        label_3->setText(QApplication::translate("configFtpWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", 0));
        label_4->setText(QApplication::translate("configFtpWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        pushButtonSaveExit->setText(QApplication::translate("configFtpWindow", "\344\277\235\345\255\230\351\200\200\345\207\272", 0));
        groupBox_3->setTitle(QApplication::translate("configFtpWindow", "ftp\345\267\245\344\275\234\347\233\256\345\275\225", 0));
        label_5->setText(QApplication::translate("configFtpWindow", "\345\267\245\344\275\234\347\233\256\345\275\225\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class configFtpWindow: public Ui_configFtpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGFTPWINDOW_H
