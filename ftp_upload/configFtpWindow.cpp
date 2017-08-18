#include "configFtpWindow.h"

configFtpWindow::configFtpWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle("Config----FTP");
	setFixedSize(400,398);


	connect(ui.pushButtonSaveExit, SIGNAL(clicked()), this, SLOT(saveExitSlot())); //保存退出

	showFtpConfigSlot();
}

configFtpWindow::~configFtpWindow()
{
}

//******************************************************slots
//显示配置信息
void configFtpWindow::showFtpConfigSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	QString userName = setting->value("ftpConfig/userName").toString();
	QString passwd = setting->value("ftpConfig/password").toString();
	QString server = setting->value("ftpConfig/server").toString();
	QString port = setting->value("ftpConfig/port").toString();
	QString workingDir = setting->value("ftpConfig/workingDir").toString();
	delete setting;

	ui.lineEditUserName->setText(userName);
	ui.lineEditPasswd->setText(passwd);
	ui.lineEditServer->setText(server);
	ui.lineEditPort->setText(port);
	ui.lineEditWorkDir->setText(workingDir);
}
//保存退出
void configFtpWindow::saveExitSlot()
{
	QString userName = ui.lineEditUserName->text();
	QString passwd = ui.lineEditPasswd->text();
	QString server = ui.lineEditServer->text();
	QString port = ui.lineEditPort->text();
	QString workingDir = ui.lineEditWorkDir->text();

	//写入ftp_config.ini文件
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/ftp_config.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	setting->setValue("ftpConfig/userName",userName);
	setting->setValue("ftpConfig/password", passwd);
	setting->setValue("ftpConfig/server", server);
	setting->setValue("ftpConfig/port", port);
	setting->setValue("ftpConfig/workingDir", workingDir);
	delete setting;
	emit saveExitSignal(0);
	this->close();
}
