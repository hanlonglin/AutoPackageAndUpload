#pragma once

#include <QWidget>
#include "ui_JsonInfoWindow.h"
#include <qsettings.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <string>
#include <iostream>
#include <qdebug.h>
#include "Crypt.h"
#include <qtextcodec.h>
#include <qtablewidget.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <qlist.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmimedata.h>
#include <qurl.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <windows.h>
#include <winver.h>
#include <qcryptographichash.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qdesktopservices.h>
#include <qprocess.h>




#pragma comment(lib,"version.lib")



class JsonInfoWindow : public QWidget
{
	Q_OBJECT

public:
	JsonInfoWindow(QWidget *parent = Q_NULLPTR);
	~JsonInfoWindow();

private:
	Ui::JsonInfoWindow ui;
	Crypt crypt;

	QString logText;

	//数据
	QString packageJsonPath;//保存package.json的文件路径
	QString realJSonInfo;   //解密后的json数据
	//
	struct FileStruct
	{
		QString name;
		QString ver;
		QString md5;
		QString reg;
		QString runorder;
		QString run;
		QString runparam;
		QString dir;
		QString protect;
	};
	int updateid,updateid_save;
	QString mainfilever,mainfilever_save;
	QList<QString> processList,processList_save;  //存储processList的程序集合
	QList<FileStruct> fileList,fileList_save;  //存储files的程序集合
	
	QList<QTableWidgetItem*> process_modifyItems; //保存已经修改processlist表的item
	QList<QTableWidgetItem*> file_modifyItems; //保存已经修改files表的item

	QList<QString> fileToBeCopy_List; //要复制的文件 --保存绝对路径
	QList<FileStruct> fileToBeDelete_List; //要删除的文件  --保存相对路径和文件名

	QProcess process;
		 

	//读package.json
	void readJson();

	//解析json
	void analysisJson();

	//显示json内容
	void showJson();

	//获取文件版本号
	QString getFileVertion(QString fullFileName);

	//获取文件md5值
	std::string getFileMd5(QString path);

	//获取文件的相对路径,相对于package.json
	QString getRelativePath(QString filePath);  //filePath 文件的绝对路径

	//获取修改信息  ---后来将写入日志
	QString getLogTxt();

	//复制文件 ，将修改和添加的文件复制
	bool copyFile(QString files);

	//删除文件，将删除的文件 删除
	void deleteFiles(QList<FileStruct> files);

	//添加文件,拖动文件到框内的操作
	void addFile(QString filePath);

	//***********************经常添加的文件
	QListWidgetItem *deleteItem;

	

private slots:

	//删除processlist的项
	void deleteProcessSlot(int row, int column);

	//添加processlist的项
	void addProcessSlot();

	//删除files项
	void deleteFileSlot(int row, int column);

	//processList表 修改item字体（当item修改时的）
	void onProcesslistTableItemChangedSlot(QTableWidgetItem *item);

	//fileList表 修改item字体（当item修改时的）
	void onFilelistTableItemChangedSlot(QTableWidgetItem *item);

	//保存修改
	void saveAllSlot();

	//接收修改信号
	//void onReceiveModifySignalSlot(QString fileName,QString action); //写日志  --未使用

	//打开日志文件
	void showLogSlot();

	//打包
	void packageSlot();

	//上传
	void uploadSlot();

	//一键打包
	void AutoPackageSlot();

	//***************************经常添加的文件
	//显示
	void showUsedFilesSlot();

	//添加
	void addUsedFilesSlot();

	//删除
	void deleteUsedFilesSlot();

	//导入
	void copyTofilesSlot();

	//选中item
	void onItemClickedSlot(QListWidgetItem *item);

	//保存经常使用的文件的打勾状态
	void saveUsedFileStateSlot();

	//***************************

protected:

	//拖拽时函数
	void dragEnterEvent(QDragEnterEvent *e);

	//松开拖拽函数
	void dropEvent(QDropEvent *e);

	//退出时函数
	void closeEvent(QCloseEvent *e);

signals:
	void exitSignal(int status);
	//void modifySignal(QString fileName,QString action);
};
