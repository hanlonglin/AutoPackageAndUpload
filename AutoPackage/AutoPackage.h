#pragma once


#include <QtWidgets/QMainWindow>
#include "ui_AutoPackage.h"
#include "JsonInfoWindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qfileinfo.h>
#include <qsettings.h>

class AutoPackage : public QMainWindow
{
	Q_OBJECT

public:
	AutoPackage(QWidget *parent = Q_NULLPTR);

private:
	Ui::AutoPackageClass ui;
	JsonInfoWindow *jsonWindow;
	
private slots:
//����·��
void setJsonSlot();

//ѡ���ļ�
void chooseJsonSlot();

//���ļ�
void openJsonSlot();

//�����˳��ź�
void revceiveExitSignal(int status);

};
