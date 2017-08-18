#include "DatabaseHelp.h"

DatabaseHelp::DatabaseHelp(QObject *parent)
	: QObject(parent)
{
	
}

DatabaseHelp::~DatabaseHelp()
{
}

/*连接数据库*/

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
	//读出数据库的参数
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath()+"/dbParam.ini",QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	url.dbName = setting->value("db/dbName").toString();
	url.pwd = setting->value("db/password").toString();
	url.uid = setting->value("db/uid").toString();
	url.host = setting->value("db/host").toString();
	url.port = setting->value("db/port").toString();
	//QMessageBox::information(NULL,"host",url.host);
	delete setting;

	//链接数据库
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

/*关闭数据库*/
bool DatabaseHelp::closeDB()
{
	if (dbConn.isOpen())
	{
		dbConn.close();
		return true;
	}
	return false;
}

/*插入数据*/
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

/*显示sql错误*/
void DatabaseHelp::showSqlError(QSqlError error)
{
	switch (error.type())
	{
	case QSqlError::ConnectionError:
		QMessageBox::information(NULL,"",QString::fromLocal8Bit("连接错误！"));
		break;
	case QSqlError::StatementError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("sql语句错误！"));
		break;
	case QSqlError::TransactionError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("事务错误！"));
		break;
	case QSqlError::UnknownError:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("未知错误！"));
		break;
	default:
		QMessageBox::information(NULL, "", QString::fromLocal8Bit("无错误！"));
		break;
	}
}