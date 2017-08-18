#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ftp_upload.h"
#include <qfile.h>
#include <qfiledialog.h>
#include <qdir.h>
#include <qmessagebox.h>
#include "configFtpWindow.h"
#include "packagejsonhelp.h"
#include "UploadHelp.h"
#include "DatabaseHelp.h"
#include <qdesktopservices.h>


class ftp_upload : public QMainWindow
{
	Q_OBJECT

public:
	ftp_upload(QWidget *parent = Q_NULLPTR);

private:
	Ui::ftp_uploadClass ui;
	configFtpWindow *configWindow;
	PackageJsonHelp *jsonHelp;
	UploadHelp *uploadHelp;

	QList<PackageJsonHelp::FileStruct> uploadFiles;  //需要上传的文件
	PackageJsonHelp::PackageInfo packageInfo; //保存updateid和mainFilever的结构体

private slots:
    
    //选择文件
void choosePathSlot();

   //开始上传
void startUploadSlot();

   //打开配置ftp
void configFtpSlot();

   //显示ftp配置
void showFtpConfigSlot();

   //显示日志
void showFtpLogSlot();

   //显示package.json路径
void showJsonPathSlot();
};
