#include "AutoPackage.h"

AutoPackage::AutoPackage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(457,165);
	setWindowTitle("Choose Json File");
	ui.lineEditPath->setFocusPolicy(Qt::NoFocus);

	

	setJsonSlot();

	connect(ui.pushButtonOpen, SIGNAL(clicked()),this,SLOT(openJsonSlot()));//打开文件
	connect(ui.pushButtonChoose,SIGNAL(clicked()),this,SLOT(chooseJsonSlot()));//选择文件
	//connect(jsonWindow,SIGNAL(exitSignal(int)),this,SLOT(revceiveExitSignal(int)));
}


//********************************************slots
//**设置文件
void AutoPackage::setJsonSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/JsonPath.ini", QSettings::IniFormat);
	QString path = setting->value("Json/path").toString();
	delete setting;
	ui.lineEditPath->setText(path);

}
//**选择文件
void AutoPackage::chooseJsonSlot()
{
	QString path = QFileDialog::getOpenFileName(this,"",QDir::currentPath(),"*.json");
	if (path.isEmpty()) return;
	ui.lineEditPath->setText(path);
	
}
//**打开文件
void AutoPackage::openJsonSlot()
{
	//判断路径是否正确
	QString path = ui.lineEditPath->text();
	if (!path.endsWith(".json"))
	{
		QMessageBox::information(this,"Waring","path is wrong!");
		return;
	}
	//写入ini
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/JsonPath.ini", QSettings::IniFormat);
	setting->setValue("Json/path",path);
	delete setting;
	jsonWindow = new JsonInfoWindow;
	connect(jsonWindow, SIGNAL(exitSignal(int)), this, SLOT(revceiveExitSignal(int)));//接受退出信号
	jsonWindow->show();
	//设置当前路径
	QFileInfo fInfo(path);
	QDir::setCurrent(fInfo.absolutePath());//设置当前路径为选择路径
	//隐藏当前界面
	this->hide();
}
//接受退出信号
void AutoPackage::revceiveExitSignal(int status)
{
	if (status==0)
	{
		this->showNormal();
	}
	if (status==1)
	{
		openJsonSlot();
		this->hide();
	}
	}