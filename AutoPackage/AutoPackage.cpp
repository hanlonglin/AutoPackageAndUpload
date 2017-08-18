#include "AutoPackage.h"

AutoPackage::AutoPackage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(457,165);
	setWindowTitle("Choose Json File");
	ui.lineEditPath->setFocusPolicy(Qt::NoFocus);

	

	setJsonSlot();

	connect(ui.pushButtonOpen, SIGNAL(clicked()),this,SLOT(openJsonSlot()));//���ļ�
	connect(ui.pushButtonChoose,SIGNAL(clicked()),this,SLOT(chooseJsonSlot()));//ѡ���ļ�
	//connect(jsonWindow,SIGNAL(exitSignal(int)),this,SLOT(revceiveExitSignal(int)));
}


//********************************************slots
//**�����ļ�
void AutoPackage::setJsonSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/JsonPath.ini", QSettings::IniFormat);
	QString path = setting->value("Json/path").toString();
	delete setting;
	ui.lineEditPath->setText(path);

}
//**ѡ���ļ�
void AutoPackage::chooseJsonSlot()
{
	QString path = QFileDialog::getOpenFileName(this,"",QDir::currentPath(),"*.json");
	if (path.isEmpty()) return;
	ui.lineEditPath->setText(path);
	
}
//**���ļ�
void AutoPackage::openJsonSlot()
{
	//�ж�·���Ƿ���ȷ
	QString path = ui.lineEditPath->text();
	if (!path.endsWith(".json"))
	{
		QMessageBox::information(this,"Waring","path is wrong!");
		return;
	}
	//д��ini
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/JsonPath.ini", QSettings::IniFormat);
	setting->setValue("Json/path",path);
	delete setting;
	jsonWindow = new JsonInfoWindow;
	connect(jsonWindow, SIGNAL(exitSignal(int)), this, SLOT(revceiveExitSignal(int)));//�����˳��ź�
	jsonWindow->show();
	//���õ�ǰ·��
	QFileInfo fInfo(path);
	QDir::setCurrent(fInfo.absolutePath());//���õ�ǰ·��Ϊѡ��·��
	//���ص�ǰ����
	this->hide();
}
//�����˳��ź�
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