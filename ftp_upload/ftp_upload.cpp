#include "ftp_upload.h"

ftp_upload::ftp_upload(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("FTP----upload");
	setFixedSize(561,549);

	connect(ui.actionConfig, SIGNAL(triggered()), this, SLOT(configFtpSlot())); //����ftp
	connect(ui.actionShowLog, SIGNAL(triggered()), this, SLOT(showFtpLogSlot()));//��ʾ��־
	connect(ui.pushButtonChoose,SIGNAL(clicked()),this,SLOT(choosePathSlot())); //ѡ���ļ�
	connect(ui.pushButtonUpload,SIGNAL(clicked()),this,SLOT(startUploadSlot())); //��ʼ�ϴ�

	jsonHelp = new PackageJsonHelp(this);
	uploadHelp = new UploadHelp(this);
	
	configWindow = new configFtpWindow;
	connect(configWindow, SIGNAL(saveExitSignal(int)), this, SLOT(showFtpConfigSlot()));
	showFtpConfigSlot(); //��ʾftp����

	showJsonPathSlot(); //��ʾpackage.json��·��

	//*************Ĭ��һ�򿪳���Ϳ�ʼ�ϴ�
	//startUploadSlot();

}


//**********************************************************************slots
//������ftp
void ftp_upload::configFtpSlot()
{
	configWindow->showNormal();
}
//��ʾftp����
void ftp_upload::showFtpConfigSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString ftpConfig;
	ftpConfig.append("userName:    "+setting->value("ftpConfig/userName").toString()+"\n");
	ftpConfig.append("password:    " + setting->value("ftpConfig/password").toString() + "\n");
	ftpConfig.append("host:        " + setting->value("ftpConfig/server").toString());
	ftpConfig.append("   port: " + setting->value("ftpConfig/port").toString() + "\n");
	ftpConfig.append("workingDir:  " + setting->value("ftpConfig/workingDir").toString());
	ui.labelFtpConfig->setText(ftpConfig);
	delete setting;
}
//��ʾ��־
void ftp_upload::showFtpLogSlot()
{
	if (!QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/upload.log")))
		QMessageBox::information(this, "", QDir::currentPath() + "/upload.log open log fail!");
}
//��ʾpackage.json·��
void ftp_upload::showJsonPathSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/JsonPath.ini", QSettings::IniFormat);
	QString path = setting->value("Json/path").toString();
	delete setting;
	ui.lineEditPath->setText(path);
	//���õ�ǰ·��
	QFileInfo finfo(path);
	QDir::setCurrent(finfo.absolutePath());
}
//ѡ���ļ�
void ftp_upload::choosePathSlot()
{
	QString path = QFileDialog::getOpenFileName(this,"",QDir::currentPath(),"*.json");
	if (path.isEmpty()) return;
	ui.lineEditPath->setText(path);
	//���õ�ǰ·��
	QFileInfo finfo(path);
	QDir::setCurrent(finfo.absolutePath());
	//д��ini
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/JsonPath.ini", QSettings::IniFormat);
	setting->setValue("Json/path", path);
	delete setting;
}
//����ϴ�
void ftp_upload::startUploadSlot()
{
	ui.textEditTest->clear();

	QString packageJsonPath = ui.lineEditPath->text();
	if (packageJsonPath.isEmpty())
	{
		QMessageBox::information(this,"","please choose a path");
		return;
	}
	QString realJsonInfo = jsonHelp->readJson(packageJsonPath);
	//QMessageBox::information(this,"jsonInfo",realJsonInfo);//***********
	uploadFiles = jsonHelp->analysisJson(realJsonInfo);
	packageInfo = jsonHelp->analysisJsonForPackageInfo(realJsonInfo);//�õ�updateid��mainFilever
	//QMessageBox::information(this,"show info:",packageInfo.updateid+","+packageInfo.mainFilever);

	if (uploadFiles.size()==0)
	{
		QMessageBox::information(this,"Waring:","No file to be upload!");
		return;
	}
	//��������
	if (!uploadHelp->connectFTP())
	{   
		//����ʧ��
		//�رղ���
		uploadHelp->closeFTP();
		return;
	}
	else {
	    //���ӳɹ�
		//�ж����޹���Ŀ¼
		if (!uploadHelp->isWorkingDirExist())  //���������
		{
			//�رղ���
			uploadHelp->closeFTP();
			return;
		}
		
	}

	
	//��ʼ�ϴ�
	//�ϴ��ļ�
	//--------------------------------------------------��ʼ�ϴ��б��ļ�
	for (int i=0;i<uploadFiles.size();i++)
	{
		QString relativePath = uploadFiles.at(i).dir+uploadFiles.at(i).name;
		QDir relativeDir(relativePath);
		QString uploadPath = relativeDir.absolutePath();
		//ui.textEditTest->append(uploadPath);
        //�ϴ�
		int ret=uploadHelp->uploadFile(uploadFiles.at(i));
		if (ret==-2)
		{
			//ftp����ʧ��
			ui.textEditTest->append("ftp connect fail!!");
		}
		if (ret==-1)
		{
		    //�ļ�������
			ui.textEditTest->append(uploadPath +" is not exist!!");
		}
		if (ret==-3)
		{
		    //�ļ�ΪĿ¼
			ui.textEditTest->append(uploadPath+" is dir!!");
		}
		if (ret==2) 
		{
		    //�ļ��Ѵ�����ftp��
			ui.textEditTest->append(uploadPath+" already in the ftp!!");
		}
		if (ret==1)
		{
			//�ɹ�
			ui.textEditTest->append(uploadPath+" upload success.");
		}
		if (ret==0)
		{
		    //ʧ��
			ui.textEditTest->append(uploadPath+" upload fail!!");
		}
	
	}
	//--------------------------------------------�ϴ��б��ļ�����
	//--------------------------------------------�ϴ�package.json
	int ret = uploadHelp->uploadPackageJson(packageJsonPath, packageInfo.updateid);
	if (ret == -2)
	{
		//ftp����ʧ��
		ui.textEditTest->append("ftp connect fail!!");
	}
	if (ret == -1)
	{
		//�ļ�������
		ui.textEditTest->append(packageJsonPath + " is not exist!!");
	}
	if (ret == -3)
	{
		//�ļ�ΪĿ¼
		ui.textEditTest->append(packageJsonPath + " is dir!!");
	}
	if (ret == 2)
	{
		//�ļ��Ѵ�����ftp��
		ui.textEditTest->append(packageJsonPath + " already in the ftp!!");
	}
	if (ret == 1)
	{
		//�ɹ�
		ui.textEditTest->append(packageJsonPath + " upload success.");
	}
	if (ret == 0)
	{
		//ʧ��
		ui.textEditTest->append(packageJsonPath + " upload fail!!");
	}

	//--------------------------------�ϴ�package.json����

	//�����ݿ��������
	DatabaseHelp dbHelp(this);
	dbHelp.insertData(packageInfo.updateid,packageInfo.mainFilever);
	

	//д��log�ļ�
	//���޸�д����־�ļ�
	QFile logFile(QCoreApplication::applicationDirPath() + "/upload.log");
	if (!logFile.open(QIODevice::ReadWrite))  //�ȶ���֮ǰ��log
	{
		QMessageBox::information(this, "Waring:", "the log.txt open fail!");
		return;
	}
	std::string log_save = logFile.readAll();
	logFile.close();

	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))  //��д�����ڵ�log
	{
		QMessageBox::information(this, "Waring:", "the upload.log open fail!");
		return;
	}
	QString logTxt;
	QString dateStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	logTxt.append("--------"+dateStr + "   on file: " + packageJsonPath + ":\n");
	logTxt.append(ui.textEditTest->toPlainText()+"\n");
	logTxt.append("-----------------------------------------------------------------------------------------------------------\n");
	logFile.write(logTxt.toLocal8Bit());
	logFile.close();
	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) //��д��֮ǰ��log
	{
		QMessageBox::information(this, "Waring:", "the  upload.log open fail!");
		return;
	}
	logFile.write(log_save.data());
	logFile.close();
	//
	QMessageBox::information(this,"","upload finished!");
}
