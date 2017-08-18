#pragma once

#include <QObject>
#define C1 52845
#define C2 22719
#include <string>
#include <qmessagebox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qdir.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>

class PackageJsonHelp : public QObject
{
	Q_OBJECT

	
public:
	PackageJsonHelp(QObject *parent);
	~PackageJsonHelp();
	
	struct FileStruct
	{
		QString name;
		QString dir;
		QString ver;
		QString md5;
	};
	struct PackageInfo
	{
		QString updateid;
		QString mainFilever;
	};
	//
	//读package.json
	QString readJson(QString packagePath);  //返回解密后的json数据

	//解析json，得到所有文件的信息
	QList<FileStruct> analysisJson(QString realJsonInfo); //返回文件集合

	//解析json，得到package.json的updateid和mainFilever
	PackageInfo analysisJsonForPackageInfo(QString realJsonInfo); //返回updateid 和mainFilever组成的结构体



private:
	std::string  Encrypt(std::string S, unsigned short Key); // 加密函数

	std::string Decrypt(std::string S, unsigned short Key);  //解密函数


	std::string EnCrypt(std::string dst, int length); // 加密函数（最终加密函数）														

	std::string DeCrpty(std::string szText, int ilen); // 解密函数(最终解密函数)
};
