/********************************************************************************
** Form generated from reading UI file 'JsonInfoWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JSONINFOWINDOW_H
#define UI_JSONINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JsonInfoWindow
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEditUpdateid;
    QLineEdit *lineEditMainFilever;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *tableWidgetProcesslist;
    QPushButton *pushButtonAddProcess;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidgetFiles;
    QPushButton *pushButtonOpenLog;
    QPushButton *pushButtonAutoPackage;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSaveAll;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonPackage;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonUpload;
    QGroupBox *groupBox_3;
    QListWidget *listWidgetShow;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonCopy;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *JsonInfoWindow)
    {
        if (JsonInfoWindow->objectName().isEmpty())
            JsonInfoWindow->setObjectName(QStringLiteral("JsonInfoWindow"));
        JsonInfoWindow->resize(1345, 585);
        groupBox = new QGroupBox(JsonInfoWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 211, 531));
        lineEditUpdateid = new QLineEdit(groupBox);
        lineEditUpdateid->setObjectName(QStringLiteral("lineEditUpdateid"));
        lineEditUpdateid->setGeometry(QRect(80, 20, 113, 20));
        lineEditMainFilever = new QLineEdit(groupBox);
        lineEditMainFilever->setObjectName(QStringLiteral("lineEditMainFilever"));
        lineEditMainFilever->setGeometry(QRect(80, 80, 113, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 71, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 130, 71, 16));
        tableWidgetProcesslist = new QTableWidget(groupBox);
        tableWidgetProcesslist->setObjectName(QStringLiteral("tableWidgetProcesslist"));
        tableWidgetProcesslist->setGeometry(QRect(10, 160, 201, 361));
        pushButtonAddProcess = new QPushButton(groupBox);
        pushButtonAddProcess->setObjectName(QStringLiteral("pushButtonAddProcess"));
        pushButtonAddProcess->setGeometry(QRect(110, 130, 75, 23));
        groupBox_2 = new QGroupBox(JsonInfoWindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 10, 741, 541));
        tableWidgetFiles = new QTableWidget(groupBox_2);
        tableWidgetFiles->setObjectName(QStringLiteral("tableWidgetFiles"));
        tableWidgetFiles->setGeometry(QRect(10, 20, 721, 501));
        pushButtonOpenLog = new QPushButton(JsonInfoWindow);
        pushButtonOpenLog->setObjectName(QStringLiteral("pushButtonOpenLog"));
        pushButtonOpenLog->setGeometry(QRect(10, 550, 91, 23));
        pushButtonAutoPackage = new QPushButton(JsonInfoWindow);
        pushButtonAutoPackage->setObjectName(QStringLiteral("pushButtonAutoPackage"));
        pushButtonAutoPackage->setGeometry(QRect(890, 550, 75, 23));
        horizontalLayoutWidget = new QWidget(JsonInfoWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(320, 550, 371, 25));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonSaveAll = new QPushButton(horizontalLayoutWidget);
        pushButtonSaveAll->setObjectName(QStringLiteral("pushButtonSaveAll"));

        horizontalLayout->addWidget(pushButtonSaveAll);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonPackage = new QPushButton(horizontalLayoutWidget);
        pushButtonPackage->setObjectName(QStringLiteral("pushButtonPackage"));

        horizontalLayout->addWidget(pushButtonPackage);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonUpload = new QPushButton(horizontalLayoutWidget);
        pushButtonUpload->setObjectName(QStringLiteral("pushButtonUpload"));

        horizontalLayout->addWidget(pushButtonUpload);

        groupBox_3 = new QGroupBox(JsonInfoWindow);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(980, 10, 361, 561));
        listWidgetShow = new QListWidget(groupBox_3);
        listWidgetShow->setObjectName(QStringLiteral("listWidgetShow"));
        listWidgetShow->setGeometry(QRect(10, 20, 341, 461));
        pushButtonEdit = new QPushButton(groupBox_3);
        pushButtonEdit->setObjectName(QStringLiteral("pushButtonEdit"));
        pushButtonEdit->setGeometry(QRect(40, 490, 75, 23));
        pushButtonCopy = new QPushButton(groupBox_3);
        pushButtonCopy->setObjectName(QStringLiteral("pushButtonCopy"));
        pushButtonCopy->setGeometry(QRect(110, 530, 75, 23));
        pushButtonDelete = new QPushButton(groupBox_3);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));
        pushButtonDelete->setGeometry(QRect(180, 490, 75, 23));

        retranslateUi(JsonInfoWindow);

        QMetaObject::connectSlotsByName(JsonInfoWindow);
    } // setupUi

    void retranslateUi(QWidget *JsonInfoWindow)
    {
        JsonInfoWindow->setWindowTitle(QApplication::translate("JsonInfoWindow", "JsonInfoWindow", 0));
        groupBox->setTitle(QApplication::translate("JsonInfoWindow", "\346\226\207\344\273\266", 0));
        label->setText(QApplication::translate("JsonInfoWindow", "updateid", 0));
        label_2->setText(QApplication::translate("JsonInfoWindow", "mainFilever:", 0));
        label_3->setText(QApplication::translate("JsonInfoWindow", "processlist:", 0));
        pushButtonAddProcess->setText(QApplication::translate("JsonInfoWindow", "\346\267\273\345\212\240\346\226\207\344\273\266", 0));
        groupBox_2->setTitle(QApplication::translate("JsonInfoWindow", "\346\226\207\344\273\266\345\210\227\350\241\250", 0));
        pushButtonOpenLog->setText(QApplication::translate("JsonInfoWindow", "\346\211\223\345\274\200\346\227\245\345\277\227\346\226\207\344\273\266", 0));
        pushButtonAutoPackage->setText(QApplication::translate("JsonInfoWindow", "\344\270\200\351\224\256\346\211\223\345\214\205", 0));
        pushButtonSaveAll->setText(QApplication::translate("JsonInfoWindow", "\347\224\237\346\210\220", 0));
        pushButtonPackage->setText(QApplication::translate("JsonInfoWindow", "\346\211\223\345\214\205", 0));
        pushButtonUpload->setText(QApplication::translate("JsonInfoWindow", "\344\270\212\344\274\240", 0));
        groupBox_3->setTitle(QApplication::translate("JsonInfoWindow", "\347\273\217\345\270\270\346\267\273\345\212\240\347\232\204\346\226\207\344\273\266", 0));
        pushButtonEdit->setText(QApplication::translate("JsonInfoWindow", "\346\267\273\345\212\240", 0));
        pushButtonCopy->setText(QApplication::translate("JsonInfoWindow", "\345\257\274\345\205\245", 0));
        pushButtonDelete->setText(QApplication::translate("JsonInfoWindow", "\345\210\240\351\231\244", 0));
    } // retranslateUi

};

namespace Ui {
    class JsonInfoWindow: public Ui_JsonInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JSONINFOWINDOW_H
