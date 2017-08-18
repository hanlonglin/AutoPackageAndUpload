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
//设置路径
void setJsonSlot();

//选择文件
void chooseJsonSlot();

//打开文件
void openJsonSlot();

//接受退出信号
void revceiveExitSignal(int status);

};
