#include "ftp_upload.h"

ftp_upload::ftp_upload(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("FTP----upload");
	setFixedSize(561,549);

	connect(ui.actionConfig, SIGNAL(triggered()), this, SLOT(configFtpSlot())); //配置ftp
	connect(ui.actionShowLog, SIGNAL(triggered()), this, SLOT(showFtpLogSlot()));//显示日志
	connect(ui.pushButtonChoose,SIGNAL(clicked()),this,SLOT(choosePathSlot())); //选择文件
	connect(ui.pushButtonUpload,SIGNAL(clicked()),this,SLOT(startUploadSlot())); //开始上传

	jsonHelp = new PackageJsonHelp(this);
	uploadHelp = new UploadHelp(this);
	
	configWindow = new configFtpWindow;
	connect(configWindow, SIGNAL(saveExitSignal(int)), this, SLOT(showFtpConfigSlot()));
	showFtpConfigSlot(); //显示ftp配置

	showJsonPathSlot(); //显示package.json的路径

	//*************默认一打开程序就开始上传
	//startUploadSlot();

}


//**********************************************************************slots
//打开配置ftp
void ftp_upload::configFtpSlot()
{
	configWindow->showNormal();
}
//显示ftp配置
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
//显示日志
void ftp_upload::showFtpLogSlot()
{
	if (!QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/upload.log")))
		QMessageBox::information(this, "", QDir::currentPath() + "/upload.log open log fail!");
}
//显示package.json路径
void ftp_upload::showJsonPathSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/JsonPath.ini", QSettings::IniFormat);
	QString path = setting->value("Json/path").toString();
	delete setting;
	ui.lineEditPath->setText(path);
	//设置当前路径
	QFileInfo finfo(path);
	QDir::setCurrent(finfo.absolutePath());
}
//选择文件
void ftp_upload::choosePathSlot()
{
	QString path = QFileDialog::getOpenFileName(this,"",QDir::currentPath(),"*.json");
	if (path.isEmpty()) return;
	ui.lineEditPath->setText(path);
	//设置当前路径
	QFileInfo finfo(path);
	QDir::setCurrent(finfo.absolutePath());
	//写入ini
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/JsonPath.ini", QSettings::IniFormat);
	setting->setValue("Json/path", path);
	delete setting;
}
//点击上传
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
	packageInfo = jsonHelp->analysisJsonForPackageInfo(realJsonInfo);//得到updateid和mainFilever
	//QMessageBox::information(this,"show info:",packageInfo.updateid+","+packageInfo.mainFilever);

	if (uploadFiles.size()==0)
	{
		QMessageBox::information(this,"Waring:","No file to be upload!");
		return;
	}
	//测试连接
	if (!uploadHelp->connectFTP())
	{   
		//连接失败
		//关闭测试
		uploadHelp->closeFTP();
		return;
	}
	else {
	    //连接成功
		//判断有无工作目录
		if (!uploadHelp->isWorkingDirExist())  //如果不存在
		{
			//关闭测试
			uploadHelp->closeFTP();
			return;
		}
		
	}

	
	//开始上传
	//上传文件
	//--------------------------------------------------开始上传列表文件
	for (int i=0;i<uploadFiles.size();i++)
	{
		QString relativePath = uploadFiles.at(i).dir+uploadFiles.at(i).name;
		QDir relativeDir(relativePath);
		QString uploadPath = relativeDir.absolutePath();
		//ui.textEditTest->append(uploadPath);
        //上传
		int ret=uploadHelp->uploadFile(uploadFiles.at(i));
		if (ret==-2)
		{
			//ftp连接失败
			ui.textEditTest->append("ftp connect fail!!");
		}
		if (ret==-1)
		{
		    //文件不存在
			ui.textEditTest->append(uploadPath +" is not exist!!");
		}
		if (ret==-3)
		{
		    //文件为目录
			ui.textEditTest->append(uploadPath+" is dir!!");
		}
		if (ret==2) 
		{
		    //文件已存在于ftp上
			ui.textEditTest->append(uploadPath+" already in the ftp!!");
		}
		if (ret==1)
		{
			//成功
			ui.textEditTest->append(uploadPath+" upload success.");
		}
		if (ret==0)
		{
		    //失败
			ui.textEditTest->append(uploadPath+" upload fail!!");
		}
	
	}
	//--------------------------------------------上传列表文件结束
	//--------------------------------------------上传package.json
	int ret = uploadHelp->uploadPackageJson(packageJsonPath, packageInfo.updateid);
	if (ret == -2)
	{
		//ftp连接失败
		ui.textEditTest->append("ftp connect fail!!");
	}
	if (ret == -1)
	{
		//文件不存在
		ui.textEditTest->append(packageJsonPath + " is not exist!!");
	}
	if (ret == -3)
	{
		//文件为目录
		ui.textEditTest->append(packageJsonPath + " is dir!!");
	}
	if (ret == 2)
	{
		//文件已存在于ftp上
		ui.textEditTest->append(packageJsonPath + " already in the ftp!!");
	}
	if (ret == 1)
	{
		//成功
		ui.textEditTest->append(packageJsonPath + " upload success.");
	}
	if (ret == 0)
	{
		//失败
		ui.textEditTest->append(packageJsonPath + " upload fail!!");
	}

	//--------------------------------上传package.json结束

	//向数据库插入数据
	DatabaseHelp dbHelp(this);
	dbHelp.insertData(packageInfo.updateid,packageInfo.mainFilever);
	

	//写入log文件
	//将修改写入日志文件
	QFile logFile(QCoreApplication::applicationDirPath() + "/upload.log");
	if (!logFile.open(QIODevice::ReadWrite))  //先读出之前的log
	{
		QMessageBox::information(this, "Waring:", "the log.txt open fail!");
		return;
	}
	std::string log_save = logFile.readAll();
	logFile.close();

	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))  //再写入现在的log
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
	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) //再写入之前的log
	{
		QMessageBox::information(this, "Waring:", "the  upload.log open fail!");
		return;
	}
	logFile.write(log_save.data());
	logFile.close();
	//
	QMessageBox::information(this,"","upload finished!");
}
