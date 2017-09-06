#pragma once

#define DB_TABLE_NAME                      "packages"
#define DB_TABLE_PARAM_PACKAGE             "package"
#define DB_TABLE_PARAM_INDATE              "indate"
#define DB_TABLE_PARAM_CREATE_USER         "createuser"
#define DB_TABLE_PARAM_MAINVER             "mainver"


#include <QObject>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery.h>
#include <QtSql\qsqlerror.h>
#include <QMessageBox>
#include <qdatetime.h>
#include <qsettings.h>
#include <qcoreapplication.h>

class DatabaseHelp : public QObject
{
	Q_OBJECT

public:
	DatabaseHelp(QObject *parent);
	~DatabaseHelp();

public :

	//连接数据库
	bool connectDB();

	//关闭
	bool closeDB();

	//插入
	bool insertData(QString updateid,QString mainFilever);

	//显示错误信息
	void showSqlError(QSqlError error);

private :

	//属性
	QSqlDatabase dbConn;
	QSqlQuery sQuery;
	struct dburl {
		QString host;
		QString port;
		QString dbName;
		QString uid;
		QString pwd;
	};
};
