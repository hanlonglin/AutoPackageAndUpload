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

	//����
	QString packageJsonPath;//����package.json���ļ�·��
	QString realJSonInfo;   //���ܺ��json����
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
	QList<QString> processList,processList_save;  //�洢processList�ĳ��򼯺�
	QList<FileStruct> fileList,fileList_save;  //�洢files�ĳ��򼯺�
	
	QList<QTableWidgetItem*> process_modifyItems; //�����Ѿ��޸�processlist���item
	QList<QTableWidgetItem*> file_modifyItems; //�����Ѿ��޸�files���item

	QList<QString> fileToBeCopy_List; //Ҫ���Ƶ��ļ� --�������·��
	QList<FileStruct> fileToBeDelete_List; //Ҫɾ�����ļ�  --�������·�����ļ���

	QProcess process;
		 

	//��package.json
	void readJson();

	//����json
	void analysisJson();

	//��ʾjson����
	void showJson();

	//��ȡ�ļ��汾��
	QString getFileVertion(QString fullFileName);

	//��ȡ�ļ�md5ֵ
	std::string getFileMd5(QString path);

	//��ȡ�ļ������·��,�����package.json
	QString getRelativePath(QString filePath);  //filePath �ļ��ľ���·��

	//��ȡ�޸���Ϣ  ---������д����־
	QString getLogTxt();

	//�����ļ� �����޸ĺ���ӵ��ļ�����
	bool copyFile(QString files);

	//ɾ���ļ�����ɾ�����ļ� ɾ��
	void deleteFiles(QList<FileStruct> files);

	//����ļ�,�϶��ļ������ڵĲ���
	void addFile(QString filePath);

	//***********************������ӵ��ļ�
	QListWidgetItem *deleteItem;

	

private slots:

	//ɾ��processlist����
	void deleteProcessSlot(int row, int column);

	//���processlist����
	void addProcessSlot();

	//ɾ��files��
	void deleteFileSlot(int row, int column);

	//processList�� �޸�item���壨��item�޸�ʱ�ģ�
	void onProcesslistTableItemChangedSlot(QTableWidgetItem *item);

	//fileList�� �޸�item���壨��item�޸�ʱ�ģ�
	void onFilelistTableItemChangedSlot(QTableWidgetItem *item);

	//�����޸�
	void saveAllSlot();

	//�����޸��ź�
	//void onReceiveModifySignalSlot(QString fileName,QString action); //д��־  --δʹ��

	//����־�ļ�
	void showLogSlot();

	//���
	void packageSlot();

	//�ϴ�
	void uploadSlot();

	//һ�����
	void AutoPackageSlot();

	//***************************������ӵ��ļ�
	//��ʾ
	void showUsedFilesSlot();

	//���
	void addUsedFilesSlot();

	//ɾ��
	void deleteUsedFilesSlot();

	//����
	void copyTofilesSlot();

	//ѡ��item
	void onItemClickedSlot(QListWidgetItem *item);

	//���澭��ʹ�õ��ļ��Ĵ�״̬
	void saveUsedFileStateSlot();

	//***************************

protected:

	//��קʱ����
	void dragEnterEvent(QDragEnterEvent *e);

	//�ɿ���ק����
	void dropEvent(QDropEvent *e);

	//�˳�ʱ����
	void closeEvent(QCloseEvent *e);

signals:
	void exitSignal(int status);
	//void modifySignal(QString fileName,QString action);
};
