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
    
    //��ʾ
void showFtpConfigSlot();

    //�����˳�
void saveExitSlot();

signals:
//�����˳��ź�
void saveExitSignal(int status);

};
