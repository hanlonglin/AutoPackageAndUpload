#pragma once

#include <QWidget>
#include "ui_configFtpWindow.h"
#include <qsettings.h>

class configFtpWindow : public QWidget
{
	Q_OBJECT

public:
	configFtpWindow(QWidget *parent = Q_NULLPTR);
	~configFtpWindow();

private:
	Ui::configFtpWindow ui;

private slots:
    
    //显示
void showFtpConfigSlot();

    //保存退出
void saveExitSlot();

signals:
//保存退出信号
void saveExitSignal(int status);

};
