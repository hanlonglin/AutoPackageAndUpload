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
	//��package.json
	QString readJson(QString packagePath);  //���ؽ��ܺ��json����

	//����json���õ������ļ�����Ϣ
	QList<FileStruct> analysisJson(QString realJsonInfo); //�����ļ�����

	//����json���õ�package.json��updateid��mainFilever
	PackageInfo analysisJsonForPackageInfo(QString realJsonInfo); //����updateid ��mainFilever��ɵĽṹ��



private:
	std::string  Encrypt(std::string S, unsigned short Key); // ���ܺ���

	std::string Decrypt(std::string S, unsigned short Key);  //���ܺ���


	std::string EnCrypt(std::string dst, int length); // ���ܺ��������ռ��ܺ�����														

	std::string DeCrpty(std::string szText, int ilen); // ���ܺ���(���ս��ܺ���)
};
