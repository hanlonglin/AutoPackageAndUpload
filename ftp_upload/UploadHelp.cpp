#include "UploadHelp.h"

UploadHelp::UploadHelp(QObject *parent)
	: QObject(parent)
{

}

UploadHelp::~UploadHelp()
{
}
//����ftp������
bool UploadHelp::connectFTP()
{
	QSettings * setting = new QSettings(QCoreApplication::applicationDirPath()+"/ftp_config.ini",QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString host = setting->value("ftpConfig/server").toString();
	QString userName = setting->value("ftpConfig/userName").toString();
	QString password = setting->value("ftpConfig/password").toString();
	//QMessageBox::information(NULL,"show","host:"+ setting->value("ftpConfig/server").toString() +",userName:"+ setting->value("ftpConfig/userName").toString() +",passwd:"+ setting->value("ftpConfig/password").toString());
	delete setting;
	hInternet = InternetOpenA("A3GS Sample", INTERNET_OPEN_TYPE_DIRECT,
		NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE);
	if (NULL == hInternet)
	{
		QMessageBox::information(NULL, "", "internet open fail");
		return false;
	}
	hConnect = InternetConnectA(hInternet, host.toLocal8Bit().data(), INTERNET_DEFAULT_FTP_PORT,
		userName.toLocal8Bit().data(),password.toLocal8Bit().data(), INTERNET_SERVICE_FTP,
		INTERNET_FLAG_EXISTING_CONNECT || INTERNET_FLAG_PASSIVE, 0);
	if (NULL == hConnect)
	{
		QMessageBox::information(NULL, "", "connect fail");
		InternetCloseHandle(hConnect);
		return false;
	}
	return true;
}
//�жϹ���Ŀ¼�Ƿ����
bool UploadHelp::isWorkingDirExist()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;
	bool initDir = FtpSetCurrentDirectoryA(hConnect, workingDir.toLocal8Bit().data());
	if (!initDir)
	{
		QMessageBox::information(NULL, "", workingDir + " is not exist in ftp!");
		return false;
	}
	return true;
}
//�ϴ��ļ�
/*
�ϴ����裺
1.����ftp��ʧ�ܷ���-2��
2.��ʼ��Ŀ¼�����õ�ǰ����Ŀ¼����hanlonglin,icc_server��
3.�ж�Ҫ�ϴ����ļ��Ƿ���ڣ�ʧ�ܷ���-1��
4.�ж�Ҫ�ϴ����ļ��Ƿ�ΪĿ¼��ʧ�ܷ���-3��
5.���õ�ǰĿ¼Ϊ�ļ����������ļ��У����ɹ�����ʾ�ļ��д��ڣ���ʼ����6�������ɹ�����ʾ�ļ��в����ڣ�ִ�����£�
     1��.�ڵ�ǰĿ¼�����ļ����������ļ��У�
     2��.���õ�ǰĿ¼Ϊ�ļ����������ļ����£�
6.�õ��ļ��İ汾�ţ�����汾��Ϊ�գ�ִ�е�8���������Ϊ�գ�ִ�е�7����
7.���õ�ǰĿ¼Ϊ�汾���������ļ��У����ɹ�����ʾ�ļ��д��ڣ���ʼ����8�������ɹ�����ʾ�ļ��в����ڣ�ִ�����£�
     1��.�ڵ�ǰĿ¼�����汾���������ļ��У�
	 2��.���õ�ǰĿ¼Ϊ�汾���������ļ����£�
8.���ļ��ϴ�����ǰĿ¼�£��ɹ�����1��ʧ�ܷ���0������ʱ�ϴ����ļ�����������Զ����ǣ���
9.�ر�ftp���ӣ�
*/
int UploadHelp::uploadFile(PackageJsonHelp::FileStruct file)
{
	QString relativePath = file.dir +file.name;
	QDir relativeDir(relativePath);
	QString filePath = relativeDir.absolutePath();  //�õ��ļ�����·��
	//�ж��ļ��Ƿ����
	QFileInfo finfo(filePath);
	QString fileName = finfo.fileName();
	if (!finfo.exists())
	{
		return -1;
	}
	//�ж��ļ��Ƿ�Ϊ�ļ���
	if (finfo.isDir())
	{
		return -3;
	}
	//����ftp
	bool ret=connectFTP();
	if (!ret) 
	{
		//�ر�ftp
		closeFTP();
		return -2;
	}
	//��ʼ����ǰĿ¼
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/ftp_config.ini",QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;
	bool initDir = FtpSetCurrentDirectoryA(hConnect, workingDir.toLocal8Bit().data());
	if (!initDir)
	{
		QMessageBox::information(NULL, "", workingDir+" is not exist in ftp!");
		//�ر�ftp
		closeFTP();
		return 0;
	}
	
	//***Winnet
	fileName.replace(":", "");
	fileName.replace("/", "");
	fileName.replace("\\", "");
	fileName.replace("?", "");
	fileName.replace("*", "");
	fileName.replace("<", "");
	fileName.replace(">", "");
	fileName.replace("|", "");
	//�ж��ļ����ļ����Ƿ����
	bool isFnameDirExist = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
	if (!isFnameDirExist)
	{
		//���������
		//�����ļ����������ļ���
		bool createFnameDir = FtpCreateDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!createFnameDir)
		{
			QMessageBox::information(NULL, "", " create dir " + fileName + " fail!");
			//�ر�ftp
			closeFTP();
			return 0;
		}
		//���õ�ǰĿ¼,�����ļ���������Ŀ¼
		bool setFnameDir = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!setFnameDir)
		{
			QMessageBox::information(NULL, "", "set current dir " + fileName + " fail");
			//�ر�ftp
			closeFTP();
			return 0;
		}
	}
	//�жϰ汾���ļ����Ƿ����
	QString version = file.ver;  //---�õ��汾��
	version.replace(":","");
	version.replace("/","");
	version.replace("\\","");
	version.replace("?","");
	version.replace("*","");
	version.replace("<", "");
	version.replace(">", "");
	version.replace("|", "");
	if (version.isEmpty()) 
	{
		QMessageBox::information(NULL, "", fileName + " 's version is empty!!");
		//�ر�ftp
		closeFTP();
		return 0;
	}
	if (!version.isEmpty())
	{
		//�ж��ļ��汾���ļ����Ƿ����
		bool isVersionDirExist = FtpSetCurrentDirectoryA(hConnect, version.toLocal8Bit().data());
		if (!isVersionDirExist)
		{
			//���������
			//�����汾���������ļ���
			bool createVersionDir = FtpCreateDirectoryA(hConnect, version.toLocal8Bit().data());
			if (!createVersionDir)
			{
				QMessageBox::information(NULL, "", fileName+ " create dir " + version + " fail!");
				//�ر�ftp
				closeFTP();
				return 0;
			}
			//���õ�ǰĿ¼,���԰汾��������Ŀ¼
			bool setVersionDir = FtpSetCurrentDirectoryA(hConnect, version.toLocal8Bit().data());
			if (!setVersionDir)
			{
				QMessageBox::information(NULL, "", fileName+" set current dir " + version + " fail");
				//�ر�ftp
				closeFTP();
				return 0;
			}
		}
		
	}
	//�ڵ�ǰĿ¼�����ļ����Ƿ��Ѵ���
	//WIN32_FIND_DATAA fd;
	//HINTERNET hFind = FtpFindFirstFileA(hConnect,"*.*", &fd, INTERNET_FLAG_RELOAD, 0);
	//if (hFind != INVALID_HANDLE_VALUE)
	//{
	//	BOOL bFind = TRUE;
	//	do
	//	{
	//		bFind = InternetFindNextFile(hFind, &fd);
	//		QString fname = QString::fromLocal8Bit(fd.cFileName);
	//		//QMessageBox::information(NULL,"fileName",fname);
	//		 //����Ѵ��ڣ����������ϴ�
	//		if (fname==file.name)
	//		{
	//			return 2;  //��ʾ�Ѵ���
	//		}
	//	}while (bFind);
	//}
	//InternetCloseHandle(hFind);
	if (isExistInFtp(file.name))
	{
		//�ر�ftp
		closeFTP();
		return 2;//��ʾ�Ѵ���
	}

	//�ϴ�
	pRes = FtpPutFileA(hConnect, filePath.toLocal8Bit().data(), fileName.toLocal8Bit().data(), FTP_TRANSFER_TYPE_ASCII, 0);
	if (pRes == 0)
	{
		//QMessageBox::information(NULL,"","upload fail");
		//�ر�ftp
		closeFTP();
		return 0;
	}
	else {
		//QMessageBox::information(NULL,"","upload success");
		//�ر�ftp
		closeFTP();
		return 1;
	}
	

}
//********************************************************************************************
//�ϴ�package.json
int UploadHelp::uploadPackageJson(QString packageJsonPath, QString updateid)
{
	//�ж��ļ��Ƿ����
	QFileInfo finfo(packageJsonPath);
	if (!finfo.exists())
	{
		return -1;
	}
	//�ж��ļ��Ƿ�Ϊ�ļ���
	if (finfo.isDir())
	{
		return -3;
	}
	//����ftp
	bool ret = connectFTP();
	if (!ret)
	{
		//�ر�ftp
		closeFTP();
		return -2;
	}
	//��ʼ����ǰĿ¼
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;
	bool initDir = FtpSetCurrentDirectoryA(hConnect, workingDir.toLocal8Bit().data());
	if (!initDir)
	{
		QMessageBox::information(NULL, "", workingDir + " is not exist in ftp!");
		//�ر�ftp
		closeFTP();
		return 0;
	}
	//�ж��ļ����ļ����Ƿ����
	QString fileName = "package";
	bool isFnameDirExist = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
	if (!isFnameDirExist)
	{
		//���������
		//�����ļ����������ļ���
		bool createFnameDir = FtpCreateDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!createFnameDir)
		{
			QMessageBox::information(NULL, "", " create dir " + fileName + " fail!");
			//�ر�ftp
			closeFTP();
			return 0;
		}
		//���õ�ǰĿ¼,�����ļ���������Ŀ¼
		bool setFnameDir = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!setFnameDir)
		{
			QMessageBox::information(NULL, "", "set current dir " + fileName + " fail");
			//�ر�ftp
			closeFTP();
			return 0;
		}
	}
	//�жϸ��º��ļ����Ƿ����
	bool isUpdateidDirExist = FtpSetCurrentDirectoryA(hConnect, updateid.toLocal8Bit().data());
	if (!isUpdateidDirExist)
	{
		//���������
		//�������º��������ļ���
		bool createVersionDir = FtpCreateDirectoryA(hConnect, updateid.toLocal8Bit().data());
		if (!createVersionDir)
		{
			QMessageBox::information(NULL, "", fileName + " create dir " + updateid + " fail!");
			//�ر�ftp
			closeFTP();
			return 0;
		}
		//���õ�ǰĿ¼,���Ը��º�������Ŀ¼
		bool setVersionDir = FtpSetCurrentDirectoryA(hConnect, updateid.toLocal8Bit().data());
		if (!setVersionDir)
		{
			QMessageBox::information(NULL, "", fileName + " set current dir " + updateid + " fail");
			//�ر�ftp
			closeFTP();
			return 0;
		}
	}
	//�ж��ļ��Ƿ��Ѿ������ڸ�Ŀ¼
	if (isExistInFtp(finfo.fileName()))
	{
		//�ر�ftp
		closeFTP();
		return 2;//��ʾ�Ѵ���
	}
	//�ϴ�
	pRes = FtpPutFileA(hConnect, packageJsonPath.toLocal8Bit().data(), finfo.fileName().toLocal8Bit().data(), FTP_TRANSFER_TYPE_ASCII, 0);
	if (pRes == 0)
	{
		//QMessageBox::information(NULL,"","upload fail");
		//�ر�ftp
		closeFTP();
		return 0;
	}
	else {
		//QMessageBox::information(NULL,"","upload success");
		//�ر�ftp
		closeFTP();
		return 1;
	}

}

//�ر�ftp
void UploadHelp::closeFTP()
{
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
}
//*******************************************
//�ж��ļ��Ƿ������ftp��ǰĿ¼��
bool UploadHelp::isExistInFtp(QString fname)
{
	WIN32_FIND_DATAA fd;
	HINTERNET hFind = FtpFindFirstFileA(hConnect, "*.*", &fd, INTERNET_FLAG_RELOAD, 0);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		BOOL bFind = TRUE;
		do
		{
			bFind = InternetFindNextFile(hFind, &fd);
			//QString qFileName = QString::fromLocal8Bit(fd.cFileName);  //�Լ����Ե�ftpʶ������
			std::string fileName =fd.cFileName;                            //254�ϵ�ftpʶ������
			QString qFileName = QString::fromStdString(fileName);
			//QMessageBox::information(NULL,"fileName", fileName);
			//����Ѵ��ڣ����������ϴ�
			if (qFileName == fname)
			{
				InternetCloseHandle(hFind);
				return true;  //��ʾ�Ѵ���
			}
		} while (bFind);
	}
	InternetCloseHandle(hFind);
	return false; //��ʾ������
}
//*************************************************************************
//�õ��ļ��İ汾��     ----δʹ��
QString UploadHelp::getFileVersion(QString fullName)
{
	//QMessageBox::information(this,"fullName",fullName);
	QString result = "";
	char* pData = nullptr;
	do
	{
		DWORD dwLen = GetFileVersionInfoSize(fullName.toStdWString().c_str(), 0);
		if (0 == dwLen)
		{
			break;
		}
		pData = new char[dwLen + 1];
		BOOL bSuccess = GetFileVersionInfo(fullName.toStdWString().c_str(), 0, dwLen, pData);
		if (!bSuccess)
		{
			break;
		}
		struct LANGANDCODEPAGE
		{
			WORD wLanguage;
			WORD wCodePage;
		} *lpTranslate;
		LPVOID lpBuffer = nullptr;
		UINT uLen = 0;
		bSuccess = VerQueryValue(pData, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&lpTranslate, &uLen);
		if (!bSuccess)
		{
			break;
		}
		QString str1, str2;
		str1.setNum(lpTranslate->wLanguage, 16);
		str2.setNum(lpTranslate->wCodePage, 16);
		str1 = "000" + str1;
		str2 = "000" + str2;
		QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
		bSuccess = VerQueryValue(pData, (verPath.toStdWString().c_str()), &lpBuffer, &uLen);
		if (!bSuccess)
		{
			break;
		}
		result = QString::fromUtf16((const unsigned short int *)lpBuffer);
	} while (false);
	if (nullptr != pData)
	{
		delete pData;
	}
	return result;

}