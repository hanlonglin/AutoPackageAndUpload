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

	//�������ݿ�
	bool connectDB();

	//�ر�
	bool closeDB();

	//����
	bool insertData(QString updateid,QString mainFilever);

	//��ʾ������Ϣ
	void showSqlError(QSqlError error);

private :

	//����
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
