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

	QList<PackageJsonHelp::FileStruct> uploadFiles;  //��Ҫ�ϴ����ļ�
	PackageJsonHelp::PackageInfo packageInfo; //����updateid��mainFilever�Ľṹ��

private slots:
    
    //ѡ���ļ�
void choosePathSlot();

   //��ʼ�ϴ�
void startUploadSlot();

   //������ftp
void configFtpSlot();

   //��ʾftp����
void showFtpConfigSlot();

   //��ʾ��־
void showFtpLogSlot();

   //��ʾpackage.json·��
void showJsonPathSlot();
};
