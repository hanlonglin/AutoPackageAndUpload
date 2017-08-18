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

	//����ftp
	bool connectFTP();

	//�жϹ���Ŀ¼�Ƿ����
	bool isWorkingDirExist();

	//�ϴ��ļ�(0:ʧ�ܣ�1���ɹ���-1���ļ�������)
	int uploadFile(PackageJsonHelp::FileStruct file);

	//�ϴ�package.json
	int uploadPackageJson(QString packageJsonPath,QString updateid);

	//�ر�ftp
	void closeFTP();

	//�ж��ļ��Ƿ������ftp��ǰĿ¼��
	bool isExistInFtp(QString fname);

private:


	BOOL pRes;
	HINTERNET hInternet;
	HINTERNET hConnect;

	//�õ��ļ��汾��
	QString getFileVersion(QString fullName);

private slots:


};
