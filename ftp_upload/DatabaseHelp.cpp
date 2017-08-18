#include "DatabaseHelp.h"

DatabaseHelp::DatabaseHelp(QObject *parent)
	: QObject(parent)
{
	
}

DatabaseHelp::~DatabaseHelp()
{
}

/*�������ݿ�*/

bool DatabaseHelp::connectDB()
{
	dburl url;
	/*
	url.dbName = "ic_server";
	url.pwd = "headsense@)!!)%!(";
	url.uid = "headsense";
	url.host = "192.168.8.254";
	url.port = "7001";
	*/
	//�������ݿ�Ĳ���
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/dbParam.ini",QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	url.dbName = setting->value("db/dbName").toString();
	url.pwd = setting->value("db/password").toString();
	url.uid = setting->value("db/uid").toString();
	url.host = setting->value("db/host").toString();
	url.port = setting->value("db/port").toString();
	//QMessageBox::information(NULL,"host",url.host);
	delete setting;

	//�������ݿ�
	dbConn = QSqlDatabase::addDatabase("QODBC");
	dbConn.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;"
		"DATABASE=%2;"
		"UID=%3;"
		"PWD=%4;").arg(url.host+","+url.port)
		.arg(url.dbName)
		.arg(url.uid)
		.arg(url.pwd));


	if (!dbConn.open())
	{
		QMessageBox::information(NULL,"",dbConn.lastError().text());
		return false;
	}
	return true;
}

/*�ر����ݿ�*/
bool DatabaseHelp::closeDB()
{
	if (dbConn.isOpen())
	{
		dbConn.close();
		return true;
	}
	return false;
}

/*��������*/
bool DatabaseHelp::insertData(QString updateid)
{
	if (!connectDB())
	{
		QMessageBox::information(NULL,"","Connect to database fail!");
		return false;
	}
	//QMessageBox::information(NULL,"connect result","connect success");
	//return false;

	sQuery = (QSqlQuery)dbConn;
	sQuery.prepare("insert into "+QString(DB_TABLE_NAME)+"("+QString(DB_TABLE_PARAM_PACKAGE)+","+QString(DB_TABLE_PARAM_INDATE)+","+QString(DB_TABLE_PARAM_CREATE_USER)+") values('"+updateid+"',getdate(),'AutoPackage')");
	bool ret = sQuery.exec();

	if (ret)
	{
		QMessageBox::information(NULL,"", "package:"+updateid+" insert into database success");
	}
	else {
		QMessageBox::information(NULL, "", "package:"+updateid+" insert into database fail!\n");
	}
	closeDB();
	return ret;
}

/*��ʾsql����*/
void DatabaseHelp::showSqlError(QSqlError error)
{
	switch (error.type())
	{
	case QSqlError::ConnectionError:
		QMessageBox::information(NULL,"",QString::fromLocal8Bit("���Ӵ���"));
		break;
	case QSqlError::StatementError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("sql������"));
		break;
	case QSqlError::TransactionError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("�������"));
		break;
	case QSqlError::UnknownError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("δ֪����"));
		break;
	default:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("�޴���"));
		break;
	}
}