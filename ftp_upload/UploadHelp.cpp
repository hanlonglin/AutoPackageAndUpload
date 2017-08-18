#include "UploadHelp.h"

UploadHelp::UploadHelp(QObject *parent)
	: QObject(parent)
{

}

UploadHelp::~UploadHelp()
{
}
//连接ftp服务器
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
//判断工作目录是否存在
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
//上传文件
/*
上传步骤：
1.连接ftp，失败返回-2；
2.初始化目录，设置当前工作目录，如hanlonglin,icc_server；
3.判断要上传的文件是否存在，失败返回-1；
4.判断要上传的文件是否为目录，失败返回-3；
5.设置当前目录为文件名命名的文件夹，若成功，表示文件夹存在，开始步骤6；若不成功，表示文件夹不存在，执行如下：
     1）.在当前目录创建文件名命名的文件夹；
     2）.设置当前目录为文件名命名的文件夹下；
6.得到文件的版本号，如果版本号为空，执行第8步；如果不为空，执行第7步；
7.设置当前目录为版本号命名的文件夹，若成功，表示文件夹存在，开始步骤8；若不成功，表示文件夹不存在，执行如下：
     1）.在当前目录创建版本号命名的文件夹；
	 2）.设置当前目录为版本号命名的文件夹下；
8.将文件上传到当前目录下，成功返回1；失败返回0；（此时上传的文件若存在则会自动覆盖）。
9.关闭ftp连接；
*/
int UploadHelp::uploadFile(PackageJsonHelp::FileStruct file)
{
	QString relativePath = file.dir +file.name;
	QDir relativeDir(relativePath);
	QString filePath = relativeDir.absolutePath();  //得到文件绝对路径
	//判断文件是否存在
	QFileInfo finfo(filePath);
	QString fileName = finfo.fileName();
	if (!finfo.exists())
	{
		return -1;
	}
	//判断文件是否为文件夹
	if (finfo.isDir())
	{
		return -3;
	}
	//连接ftp
	bool ret=connectFTP();
	if (!ret) 
	{
		//关闭ftp
		closeFTP();
		return -2;
	}
	//初始化当前目录
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/ftp_config.ini",QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;
	bool initDir = FtpSetCurrentDirectoryA(hConnect, workingDir.toLocal8Bit().data());
	if (!initDir)
	{
		QMessageBox::information(NULL, "", workingDir+" is not exist in ftp!");
		//关闭ftp
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
	//判断文件名文件夹是否存在
	bool isFnameDirExist = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
	if (!isFnameDirExist)
	{
		//如果不存在
		//创建文件名命名的文件夹
		bool createFnameDir = FtpCreateDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!createFnameDir)
		{
			QMessageBox::information(NULL, "", " create dir " + fileName + " fail!");
			//关闭ftp
			closeFTP();
			return 0;
		}
		//设置当前目录,即以文件名命名的目录
		bool setFnameDir = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!setFnameDir)
		{
			QMessageBox::information(NULL, "", "set current dir " + fileName + " fail");
			//关闭ftp
			closeFTP();
			return 0;
		}
	}
	//判断版本号文件夹是否存在
	QString version = file.ver;  //---得到版本号
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
		//关闭ftp
		closeFTP();
		return 0;
	}
	if (!version.isEmpty())
	{
		//判断文件版本号文件夹是否存在
		bool isVersionDirExist = FtpSetCurrentDirectoryA(hConnect, version.toLocal8Bit().data());
		if (!isVersionDirExist)
		{
			//如果不存在
			//创建版本号命名的文件夹
			bool createVersionDir = FtpCreateDirectoryA(hConnect, version.toLocal8Bit().data());
			if (!createVersionDir)
			{
				QMessageBox::information(NULL, "", fileName+ " create dir " + version + " fail!");
				//关闭ftp
				closeFTP();
				return 0;
			}
			//设置当前目录,即以版本号命名的目录
			bool setVersionDir = FtpSetCurrentDirectoryA(hConnect, version.toLocal8Bit().data());
			if (!setVersionDir)
			{
				QMessageBox::information(NULL, "", fileName+" set current dir " + version + " fail");
				//关闭ftp
				closeFTP();
				return 0;
			}
		}
		
	}
	//在当前目录查找文件，是否已存在
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
	//		 //如果已存在，则跳过不上传
	//		if (fname==file.name)
	//		{
	//			return 2;  //表示已存在
	//		}
	//	}while (bFind);
	//}
	//InternetCloseHandle(hFind);
	if (isExistInFtp(file.name))
	{
		//关闭ftp
		closeFTP();
		return 2;//表示已存在
	}

	//上传
	pRes = FtpPutFileA(hConnect, filePath.toLocal8Bit().data(), fileName.toLocal8Bit().data(), FTP_TRANSFER_TYPE_ASCII, 0);
	if (pRes == 0)
	{
		//QMessageBox::information(NULL,"","upload fail");
		//关闭ftp
		closeFTP();
		return 0;
	}
	else {
		//QMessageBox::information(NULL,"","upload success");
		//关闭ftp
		closeFTP();
		return 1;
	}
	

}
//********************************************************************************************
//上传package.json
int UploadHelp::uploadPackageJson(QString packageJsonPath, QString updateid)
{
	//判断文件是否存在
	QFileInfo finfo(packageJsonPath);
	if (!finfo.exists())
	{
		return -1;
	}
	//判断文件是否为文件夹
	if (finfo.isDir())
	{
		return -3;
	}
	//连接ftp
	bool ret = connectFTP();
	if (!ret)
	{
		//关闭ftp
		closeFTP();
		return -2;
	}
	//初始化当前目录
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;
	bool initDir = FtpSetCurrentDirectoryA(hConnect, workingDir.toLocal8Bit().data());
	if (!initDir)
	{
		QMessageBox::information(NULL, "", workingDir + " is not exist in ftp!");
		//关闭ftp
		closeFTP();
		return 0;
	}
	//判断文件名文件夹是否存在
	QString fileName = "package";
	bool isFnameDirExist = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
	if (!isFnameDirExist)
	{
		//如果不存在
		//创建文件名命名的文件夹
		bool createFnameDir = FtpCreateDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!createFnameDir)
		{
			QMessageBox::information(NULL, "", " create dir " + fileName + " fail!");
			//关闭ftp
			closeFTP();
			return 0;
		}
		//设置当前目录,即以文件名命名的目录
		bool setFnameDir = FtpSetCurrentDirectoryA(hConnect, fileName.toLocal8Bit().data());
		if (!setFnameDir)
		{
			QMessageBox::information(NULL, "", "set current dir " + fileName + " fail");
			//关闭ftp
			closeFTP();
			return 0;
		}
	}
	//判断更新号文件夹是否存在
	bool isUpdateidDirExist = FtpSetCurrentDirectoryA(hConnect, updateid.toLocal8Bit().data());
	if (!isUpdateidDirExist)
	{
		//如果不存在
		//创建更新号命名的文件夹
		bool createVersionDir = FtpCreateDirectoryA(hConnect, updateid.toLocal8Bit().data());
		if (!createVersionDir)
		{
			QMessageBox::information(NULL, "", fileName + " create dir " + updateid + " fail!");
			//关闭ftp
			closeFTP();
			return 0;
		}
		//设置当前目录,即以更新号命名的目录
		bool setVersionDir = FtpSetCurrentDirectoryA(hConnect, updateid.toLocal8Bit().data());
		if (!setVersionDir)
		{
			QMessageBox::information(NULL, "", fileName + " set current dir " + updateid + " fail");
			//关闭ftp
			closeFTP();
			return 0;
		}
	}
	//判断文件是否已经存在在该目录
	if (isExistInFtp(finfo.fileName()))
	{
		//关闭ftp
		closeFTP();
		return 2;//表示已存在
	}
	//上传
	pRes = FtpPutFileA(hConnect, packageJsonPath.toLocal8Bit().data(), finfo.fileName().toLocal8Bit().data(), FTP_TRANSFER_TYPE_ASCII, 0);
	if (pRes == 0)
	{
		//QMessageBox::information(NULL,"","upload fail");
		//关闭ftp
		closeFTP();
		return 0;
	}
	else {
		//QMessageBox::information(NULL,"","upload success");
		//关闭ftp
		closeFTP();
		return 1;
	}

}

//关闭ftp
void UploadHelp::closeFTP()
{
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
}
//*******************************************
//判断文件是否存在于ftp当前目录下
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
			//QString qFileName = QString::fromLocal8Bit(fd.cFileName);  //自己电脑的ftp识别中文
			std::string fileName =fd.cFileName;                            //254上的ftp识别中文
			QString qFileName = QString::fromStdString(fileName);
			//QMessageBox::information(NULL,"fileName", fileName);
			//如果已存在，则跳过不上传
			if (qFileName == fname)
			{
				InternetCloseHandle(hFind);
				return true;  //表示已存在
			}
		} while (bFind);
	}
	InternetCloseHandle(hFind);
	return false; //表示不存在
}
//*************************************************************************
//得到文件的版本号     ----未使用
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