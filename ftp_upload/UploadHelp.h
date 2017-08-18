#pragma once
#define _AFXDLL
#include <QObject>
#include <qmessagebox.h>
#include <qfile.h>
#include <qurl.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qsettings.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qcoreapplication.h>
#include <afxinet.h>
#include <Windows.h>
#include <winver.h>
#include "PackageJsonHelp.h"
#include <iostream>
#pragma comment(lib,"version.lib")


class UploadHelp : public QObject
{
	Q_OBJECT

public:
	UploadHelp(QObject *parent);
	~UploadHelp();

	//连接ftp
	bool connectFTP();

	//判断工作目录是否存在
	bool isWorkingDirExist();

	//上传文件(0:失败；1：成功；-1：文件不存在)
	int uploadFile(PackageJsonHelp::FileStruct file);

	//上传package.json
	int uploadPackageJson(QString packageJsonPath,QString updateid);

	//关闭ftp
	void closeFTP();

	//判断文件是否存在于ftp当前目录下
	bool isExistInFtp(QString fname);

private:


	BOOL pRes;
	HINTERNET hInternet;
	HINTERNET hConnect;

	//得到文件版本号
	QString getFileVersion(QString fullName);

private slots:


};
