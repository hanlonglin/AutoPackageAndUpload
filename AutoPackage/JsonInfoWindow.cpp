#include "JsonInfoWindow.h"


JsonInfoWindow::JsonInfoWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//页面设置
	setFixedSize(1345, 580);
	this->setAcceptDrops(true);
	ui.lineEditMainFilever->setAcceptDrops(false);
	ui.lineEditUpdateid->setAcceptDrops(false);
	//ui.lineEditUpdateid->setFocusPolicy(Qt::NoFocus);
	setWindowTitle("AutoPackage");


	readJson();  //读出并解密json内容，并保存在realJsonInfo中
	analysisJson(); //解析realJsonInfo 并将数据保存在变量中
	showJson();    //将变量显示

	connect(ui.tableWidgetProcesslist, SIGNAL(cellClicked(int, int)), this, SLOT(deleteProcessSlot(int, int)));  //删除行
	connect(ui.pushButtonAddProcess, SIGNAL(clicked()), this, SLOT(addProcessSlot()));
	connect(ui.tableWidgetFiles, SIGNAL(cellClicked(int, int)), this, SLOT(deleteFileSlot(int, int)));    //删除行
	connect(ui.tableWidgetProcesslist, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onProcesslistTableItemChangedSlot(QTableWidgetItem*))); //修改
	connect(ui.tableWidgetFiles, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onFilelistTableItemChangedSlot(QTableWidgetItem*)));   //修改

	connect(ui.pushButtonSaveAll, SIGNAL(clicked()), this, SLOT(saveAllSlot()));//保存全部

	connect(ui.pushButtonOpenLog, SIGNAL(clicked()), this, SLOT(showLogSlot())); //打开日志文件

	connect(ui.pushButtonPackage, SIGNAL(clicked()), this, SLOT(packageSlot())); //打包

	connect(ui.pushButtonUpload, SIGNAL(clicked()), this, SLOT(uploadSlot())); //上传

	connect(ui.pushButtonAutoPackage, SIGNAL(clicked()), this, SLOT(AutoPackageSlot())); //一键打包


	//***************************经常使用的文件
	connect(ui.pushButtonEdit, SIGNAL(clicked()), this, SLOT(addUsedFilesSlot())); //添加
	connect(ui.pushButtonDelete, SIGNAL(clicked()), this, SLOT(deleteUsedFilesSlot()));//删除
	connect(ui.pushButtonCopy, SIGNAL(clicked()), this, SLOT(copyTofilesSlot()));//导入
	connect(ui.listWidgetShow, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClickedSlot(QListWidgetItem*))); //选中
	showUsedFilesSlot();

	//connect(this,SIGNAL(modifySignal(QString,QString)),this,SLOT(onReceiveModifySignalSlot(QString,QString)));
}

JsonInfoWindow::~JsonInfoWindow()
{

}

//读出json并解密
void JsonInfoWindow::readJson()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/JsonPath.ini", QSettings::IniFormat);
	packageJsonPath = setting->value("Json/path").toString();
	QFile *file = new QFile(packageJsonPath);
	if (!file->open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, "Waring", "file open fail");
		return;
	}
	std::string jsonResult = file->readAll();
	//解密
	jsonResult = crypt.DeCrpty(jsonResult.c_str(), jsonResult.length());
	//转码
	//realJSonInfo = UTF8code->toUnicode(jsonResult.data());;//解密后的json
	realJSonInfo = QString::fromLocal8Bit(jsonResult.data());
	//realJSonInfo = UTF8code->fromUnicode(realJSonInfo.toStdString().data())
	//ui.textEditFile->setText(realJSonInfo);
	file->close();
	delete file;
}
//解析json
void JsonInfoWindow::analysisJson()
{
	processList.clear();
	fileList.clear();
	QJsonDocument document = QJsonDocument::fromJson(realJSonInfo.toUtf8());
	QJsonObject obj = document.object();
	updateid = obj["updateid"].toInt();
	//QMessageBox::information(this,"read updateid",QString::number(updateid));//
	mainfilever = obj["mainfilever"].toString();
	QJsonArray processListJson = obj["processlist"].toArray();
	for (int i = 0; i < processListJson.size(); i++)
	{
		QString exe = processListJson.at(i).toString();
		processList.push_back(exe);
	}
	QJsonArray filesJson = obj["files"].toArray();
	for (int i = 0; i < filesJson.size(); i++)
	{
		FileStruct file;
		QJsonObject fileObj = filesJson.at(i).toObject();
		file.name = fileObj["name"].toString();
		file.ver = fileObj["ver"].toString();
		file.md5 = fileObj["md5"].toString();
		file.reg = fileObj["reg"].toString();
		file.runorder = fileObj["runorder"].toString();
		file.run = fileObj["run"].toString();
		file.runparam = fileObj["runparam"].toString();
		file.dir = fileObj["dir"].toString();
		file.protect = fileObj["protect"].toString();
		fileList.push_back(file);
	}

}
//显示json
void JsonInfoWindow::showJson()
{
	ui.lineEditUpdateid->setText(QString::number(updateid));
	ui.lineEditMainFilever->setText(mainfilever);

	//设置processlist表
	ui.tableWidgetProcesslist->clear();
	ui.tableWidgetProcesslist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidgetProcesslist->setColumnCount(2);
	ui.tableWidgetProcesslist->setRowCount(processList.size());
	QStringList processHeader;
	processHeader << "processlist" << "";
	ui.tableWidgetProcesslist->setHorizontalHeaderLabels(processHeader);
	for (int i = 0; i < processList.size(); i++)
	{
		ui.tableWidgetProcesslist->setItem(i, 0, new QTableWidgetItem(processList.at(i)));
		QTableWidgetItem *deleteItem = new QTableWidgetItem;
		deleteItem->setText("delete");
		deleteItem->setFlags(Qt::ItemIsEditable);
		ui.tableWidgetProcesslist->setItem(i, 1, deleteItem);
	}

	//设置files表
	ui.tableWidgetFiles->clear();
	ui.tableWidgetFiles->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.tableWidgetFiles->setColumnCount(10);
	ui.tableWidgetFiles->setRowCount(fileList.size());
	QStringList filesHeader;
	filesHeader << "name" << "ver" << "md5" << "reg" << "runorder" << "run" << "runparam" << "dir" << "protect" << "";
	ui.tableWidgetFiles->setHorizontalHeaderLabels(filesHeader);
	for (int i = 0; i < fileList.size(); i++)
	{
		FileStruct file = fileList.at(i);
		ui.tableWidgetFiles->setItem(i, 0, new QTableWidgetItem(file.name));
		ui.tableWidgetFiles->setItem(i, 1, new QTableWidgetItem(file.ver));
		ui.tableWidgetFiles->setItem(i, 2, new QTableWidgetItem(file.md5));
		ui.tableWidgetFiles->setItem(i, 3, new QTableWidgetItem(file.reg));
		ui.tableWidgetFiles->setItem(i, 4, new QTableWidgetItem(file.runorder));
		ui.tableWidgetFiles->setItem(i, 5, new QTableWidgetItem(file.run));
		ui.tableWidgetFiles->setItem(i, 6, new QTableWidgetItem(file.runparam));
		ui.tableWidgetFiles->setItem(i, 7, new QTableWidgetItem(file.dir));
		ui.tableWidgetFiles->setItem(i, 8, new QTableWidgetItem(file.protect));
		QTableWidgetItem *deleteItem = new QTableWidgetItem;
		deleteItem->setText("delete");
		deleteItem->setFlags(Qt::ItemIsEditable);
		ui.tableWidgetFiles->setItem(i, 9, deleteItem);
	}

}
//得到文件的版本号
QString JsonInfoWindow::getFileVertion(QString fullName)
{
	//QMessageBox::information(this,"fullName",fullName);
	QString result = "";
	char* pData = nullptr;
	do
	{
		DWORD dwLen = GetFileVersionInfoSize(fullName.toStdWString().c_str(), 0);
		if (0 == dwLen)
		{
			break;
		}
		pData = new char[dwLen + 1];
		BOOL bSuccess = GetFileVersionInfo(fullName.toStdWString().c_str(), 0, dwLen, pData);
		if (!bSuccess)
		{
			break;
		}
		struct LANGANDCODEPAGE
		{
			WORD wLanguage;
			WORD wCodePage;
		} *lpTranslate;
		LPVOID lpBuffer = nullptr;
		UINT uLen = 0;
		bSuccess = VerQueryValue(pData, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&lpTranslate, &uLen);
		if (!bSuccess)
		{
			break;
		}
		QString str1, str2;
		str1.setNum(lpTranslate->wLanguage, 16);
		str2.setNum(lpTranslate->wCodePage, 16);
		str1 = "000" + str1;
		str2 = "000" + str2;
		QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
		bSuccess = VerQueryValue(pData, (verPath.toStdWString().c_str()), &lpBuffer, &uLen);
		if (!bSuccess)
		{
			break;
		}
		result = QString::fromUtf16((const unsigned short int *)lpBuffer);
	} while (false);
	if (nullptr != pData)
	{
		delete pData;
	}
	return result;

}
//得到文件的md5值
std::string JsonInfoWindow::getFileMd5(QString filePath)
{
	QFile theFile(filePath);
	theFile.open(QIODevice::ReadOnly);
	QByteArray ba = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
	theFile.close();
	std::string md5 = ba.toHex().constData();
	return md5;
}
//得到文件的相对路径（相对于package.json）
QString JsonInfoWindow::getRelativePath(QString filePath)
{
	QFileInfo fInfo(packageJsonPath);
	QString currentPath = fInfo.absolutePath();
	QFileInfo fInfo2(filePath);
	QString fileName = fInfo2.fileName(); //得到文件名
	QDir currentDir(currentPath);
	QString relativePath = currentDir.relativeFilePath(filePath);
	relativePath = relativePath.mid(0, relativePath.indexOf(fileName));
	return relativePath;
}
//得到日志信息
QString JsonInfoWindow::getLogTxt()
{
	QString logTxt = "";
	QString dateStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	logTxt.append(dateStr + "   on file: " + packageJsonPath + ":\n");
	/*
	通过对比读取时和保存时的信息，得出修改信息
	*/
	//updateid
	//QMessageBox::information(this,"","updateid:"+QString::number(updateid)+",updateid_save:"+QString::number(updateid_save));
	if (updateid != updateid_save)
	{
		logTxt.append("  updateid changes: \n                  " + QString::number(updateid) + " to " + QString::number(updateid_save) + ";\n");
	}
	//mainfilever
	if (mainfilever != mainfilever_save)
	{
		logTxt.append("  mainfilever changes: \n                  " + mainfilever + " to " + mainfilever_save + ";\n");
	}
	//processlist
	logTxt.append("  process changes:\n");
	for (int i = 0; i < processList_save.size(); i++)  	    //先查看添加项
	{
		QString exeName = processList_save.at(i);
		bool isExist = false;
		for (int j = 0; j < processList.size(); j++)
		{
			if (processList.at(j) == exeName)
				isExist = true;
		}
		//如果不存在 证明是新添加
		if (!isExist)
		{
			logTxt.append("                  " + exeName + " added;\n");
		}
	}
	for (int i = 0; i < processList.size(); i++)  	    //查看删除项
	{
		QString exeName = processList.at(i);
		bool isExist = false;
		for (int j = 0; j < processList_save.size(); j++)
		{
			if (processList_save.at(j) == exeName)
				isExist = true;
		}
		//如果不存在 证明是已删除
		if (!isExist)
		{
			logTxt.append("                  " + exeName + " deleted;\n");
		}
	}
	//fileList
	logTxt.append("  files changes:\n");
	for (int i = 0; i < fileList_save.size(); i++)   //查看添加项和修改项
	{
		FileStruct file = fileList_save.at(i);
		bool isExist = false;
		for (int j = 0; j < fileList.size(); j++)
		{
			if (file.name == fileList.at(j).name)
			{
				isExist = true;
				if (file.ver != fileList.at(j).ver)
					logTxt.append("                  " + file.name + "'s ver changes from " + fileList.at(j).ver + " to " + file.ver + ";\n");
				if (file.md5 != fileList.at(j).md5)
					logTxt.append("                  " + file.name + "'s md5 changes from " + fileList.at(j).md5 + " to " + file.md5 + ";\n");
				if (file.dir != fileList.at(j).dir)
					logTxt.append("                  " + file.name + "'s dir changes from " + fileList.at(j).dir + " to " + file.dir + ";\n");
				if (file.run != fileList.at(j).run)
					logTxt.append("                  " + file.name + "'s run changes from " + fileList.at(j).run + " to " + file.run + ";\n");
				if (file.runorder != fileList.at(j).runorder)
					logTxt.append("                  " + file.name + "'s runorder changes from " + fileList.at(j).runorder + " to " + file.runorder + ";\n");
				if (file.reg != fileList.at(j).reg)
					logTxt.append("                  " + file.name + "'s reg changes from " + fileList.at(j).reg + " to " + file.reg + ";\n");
				if (file.runparam != fileList.at(j).runparam)
					logTxt.append("                  " + file.name + "'s runparam changes from " + fileList.at(j).runparam + " to " + file.runparam + ";\n");
				if (file.protect != fileList.at(j).protect)
					logTxt.append("                  " + file.name + "'s protect changes from " + fileList.at(j).protect + " to " + file.protect + ";\n");
			}

		}
		//不存在 证明是新加项
		if (!isExist)
		{
			logTxt.append("                  " + file.name + " added;\n");
		}

	}
	for (int i = 0; i < fileList.size(); i++)
	{
		FileStruct file = fileList.at(i);
		bool isExist = false;
		for (int j = 0; j < fileList_save.size(); j++)
		{
			if (file.name == fileList_save.at(j).name)
				isExist = true;
		}
		//如果不存在 则为已删除项
		if (!isExist)
		{
			logTxt.append("                  " + file.name + " deleted;\n");
		}
	}
	logTxt.append("------------------------------------------------------------------------------------------------------\n");
	return logTxt;
}
//复制文件
bool JsonInfoWindow::copyFile(QString file)
{
	bool b=true;
	//QMessageBox::information(this,"file size",QString::number(files.size()));
	QString sourcePath = file;
		QFileInfo info(sourcePath);
		QDir sourceDir(info.absolutePath()); //原文件夹
		QString fileName = info.fileName();
		QList<QTableWidgetItem*> items = ui.tableWidgetFiles->findItems(fileName, Qt::MatchExactly);
		if (items.size() != 0)
		{
			//得到路径
			QString relativePath = ui.tableWidgetFiles->item(items.at(0)->row(), 7)->text();
			//QMessageBox::information(this, "currentPath", QDir::currentPath());
			//QMessageBox::information(this, "applicationPath", QCoreApplication::applicationDirPath());
			//QMessageBox::information(this, "relativePath", relativePath);
			QDir relativeDir(relativePath);
			QString copyToPath = relativeDir.absolutePath();
			//QMessageBox::information(this,"copyToPath",copyToPath);
			//开始复制
			
			QDir targetDir(copyToPath);  //目的文件夹
			if (!sourceDir.exists()||!info.exists())
			{
				QMessageBox::information(this, "Waring:", fileName + " copy to " + copyToPath + " fail!\n" + sourcePath + " is not exist!");
				return false;
			
			}
			if (!targetDir.exists())
			{
				QMessageBox::information(this, "Waring:", fileName + " copy to " + copyToPath + " fail!\n" + copyToPath + " is not exist!");
				return false;
			
			}
			
			//目的路径与原路径相同,跳过
			if (info.filePath() == targetDir.filePath(fileName)) //若路径相同，则跳过
			{
				//QMessageBox::information(NULL,"","the same dir");
				return true;
			}
			//目的文件夹存在该文件
			if (targetDir.exists(fileName))
			{
				targetDir.remove(fileName); //若存在，则删除
			}

			if (!QFile::copy(info.filePath(), targetDir.filePath(fileName)))
			{
				//失败
				QMessageBox::information(this, "", fileName + " copy to " + copyToPath + " fail!");
				return false;
				
			}
			else {
				//成功
				return true;
			}

		}
	

}
//删除文件
void JsonInfoWindow::deleteFiles(QList<FileStruct> files)
{
	for (int i = 0; i < files.size(); i++)
	{
		FileStruct fileStruct = files.at(i);
		QString fileName = fileStruct.name;
		QDir relativeDir(fileStruct.dir);
		QString deletePath = relativeDir.absolutePath();
		QDir targetDir(deletePath);
		//QMessageBox::information(this,"","fileName:"+fileName+",deletePath:"+deletePath);
		if (!targetDir.exists())
		{
			QMessageBox::information(this, "Waring:", deletePath + " is not exist!");
			return;
		}
		if (targetDir.exists(fileName))
		{
			targetDir.remove(fileName); //若存在，则删除
		}
		else
		{
			QMessageBox::information(this, "Waring:", fileName + " doesn't exist in " + deletePath + " !");
			return;
		}
	}

}
//添加文件  拖动文件到框内的操作
void JsonInfoWindow::addFile(QString filePath)
{
	QFileInfo fileInfo(filePath);
	//判断路径是否存在
	if (!fileInfo.exists())
	{
		QMessageBox::information(this,"Waring:",filePath+" is not exist!");
		return;
	}

	QString fileName = fileInfo.fileName();
	QString fileVertion = getFileVertion(filePath); //得到版本号
	QString md5 = QString::fromStdString(getFileMd5(filePath)); //得到md5
	QString relativePath = getRelativePath(filePath); //得到相对路径
													  //QMessageBox::information(this,"version",fileVertion);
													  //判断是否存在
													  //若存在替换md5
	QList<QTableWidgetItem*> itemList = ui.tableWidgetFiles->findItems(fileName, Qt::MatchExactly);
	if (!itemList.size() == 0)
	{
		//已存在，
		QMessageBox box;
		box.setText(fileName + " already exist,\n new version: " + fileVertion + " \n new md5: " + md5 + "\n Do you want to cover it ?");
		box.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
		if (box.exec() == QMessageBox::Cancel) return;
		//替换md5值
		int row_index = itemList.at(0)->row();//获取所在的行
		if (!fileVertion.isEmpty())  //如果版本号不为空
		{
			ui.tableWidgetFiles->item(row_index, 1)->setText(fileVertion);//替换版本号
		}
		ui.tableWidgetFiles->item(row_index, 2)->setText(md5); //替换md5
															   //ui.tableWidgetFiles->item(row_index, 7)->setText(relativePath);//替换相对路径

															   //emit modifySignal(ui.tableWidgetFiles->item(row_index, 0)->text(), "modified");
		fileToBeCopy_List.push_back(filePath); //保存要复制的文件路径 ，在保存时一起复制
	}
	else
	{
		//不存在添加
		ui.tableWidgetFiles->setRowCount(ui.tableWidgetFiles->rowCount() + 1);
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 0, new QTableWidgetItem(fileName));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 1, new QTableWidgetItem(fileVertion));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 2, new QTableWidgetItem(md5));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 3, new QTableWidgetItem(""));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 4, new QTableWidgetItem(""));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 5, new QTableWidgetItem(""));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 6, new QTableWidgetItem(""));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 7, new QTableWidgetItem(""));
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 8, new QTableWidgetItem(""));
		QTableWidgetItem *deleteItem = new QTableWidgetItem;
		deleteItem->setText("delete");
		deleteItem->setFlags(Qt::ItemIsEditable);
		ui.tableWidgetFiles->setItem(ui.tableWidgetFiles->rowCount() - 1, 9, deleteItem);

		ui.tableWidgetFiles->editItem(ui.tableWidgetFiles->item(ui.tableWidgetFiles->rowCount() - 1,7));
		//emit modifySignal(ui.tableWidgetFiles->item(ui.tableWidgetFiles->rowCount() - 1, 0)->text(), "added");
		fileToBeCopy_List.push_back(filePath); //保存要复制的文件路径 ，在保存时一起复制
	}
}

//*****************************************************************slots
//删除processlist的项
void JsonInfoWindow::deleteProcessSlot(int row, int column)
{
	if (column != 1) return;
	QMessageBox box;
	box.setText("Are you sure to delete the " + QString::number(row + 1) + " row?");
	box.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	int ret = box.exec();
	if (ret == QMessageBox::Cancel) return;
	QString fileName = ui.tableWidgetProcesslist->item(row, 0)->text();
	ui.tableWidgetProcesslist->removeRow(row);

	//emit modifySignal(fileName,"delete");
}
//添加processList的项
void JsonInfoWindow::addProcessSlot()
{
	ui.tableWidgetProcesslist->setRowCount(ui.tableWidgetProcesslist->rowCount() + 1);
	ui.tableWidgetProcesslist->setItem(ui.tableWidgetProcesslist->rowCount() - 1, 0, new QTableWidgetItem(""));
	QTableWidgetItem *deleteItem = new QTableWidgetItem;
	deleteItem->setText("delete");
	deleteItem->setFlags(Qt::ItemIsEditable);
	ui.tableWidgetProcesslist->setItem(ui.tableWidgetProcesslist->rowCount() - 1, 1, deleteItem);
	ui.tableWidgetProcesslist->editItem(ui.tableWidgetProcesslist->item(ui.tableWidgetProcesslist->rowCount() - 1, 0));

	//emit modifySignal(ui.tableWidgetProcesslist->item(ui.tableWidgetProcesslist->rowCount() - 1,0)->text(),"added");
}
//删除files的项
void JsonInfoWindow::deleteFileSlot(int row, int column)
{
	if (column != 9) return;
	QMessageBox box;
	box.setText("Are you sure to delete the " + QString::number(row + 1) + " row?");
	box.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	int ret = box.exec();
	if (ret == QMessageBox::Cancel) return;
	//**************************加入到删除集合
	FileStruct fileStruct;
	fileStruct.name = ui.tableWidgetFiles->item(row, 0)->text();
	//QMessageBox::information(this,"add name", fileStruct.name);
	fileStruct.dir = ui.tableWidgetFiles->item(row, 7)->text();
	fileToBeDelete_List.push_back(fileStruct); //加入到删除集合
	//**************************
	QString fileName = ui.tableWidgetFiles->item(row, 0)->text();
	ui.tableWidgetFiles->removeRow(row);


	//emit modifySignal(fileName,"delete");

}
//processList表 修改item字体（当item改变时）
void JsonInfoWindow::onProcesslistTableItemChangedSlot(QTableWidgetItem *item)
{
	QFont font;
	font.setBold(true);
	font.setItalic(true);
	item->setFont(font);

	//emit modifySignal(item->text(),"modified");

}
//fileList表 修改item字体（当item改变时）
void JsonInfoWindow::onFilelistTableItemChangedSlot(QTableWidgetItem *item)
{
	QFont font;
	font.setBold(true);
	font.setItalic(true);
	item->setFont(font);

	//emit modifySignal(item->text(), "modified");

}
//保存全部修改
void JsonInfoWindow::saveAllSlot()
{
	processList_save.clear();
	fileList_save.clear();
	readJson();
	analysisJson();
	QMessageBox box;
	box.setText("Save all changes?");
	box.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	if (box.exec() == QMessageBox::Cancel) return;
	//获取当前信息
	//*********************************************************************
	QJsonObject obj;
	obj.insert("updateid", ui.lineEditUpdateid->text().trimmed().toInt() + 1);
	updateid_save = ui.lineEditUpdateid->text().trimmed().toInt() + 1; //保存到updateid_save里
	//obj.insert("mainfilever", ui.lineEditMainFilever->text().trimmed());
	mainfilever_save = ui.lineEditMainFilever->text().trimmed(); //保存到mainfilever_save里
	QJsonArray processList_array;
	for (int i = 0; i < ui.tableWidgetProcesslist->rowCount(); i++)
	{
		processList_array.append(ui.tableWidgetProcesslist->item(i, 0)->text().trimmed());
		processList_save.push_back(ui.tableWidgetProcesslist->item(i, 0)->text().trimmed());//保存到processList_save里
	}
	obj.insert("processlist", processList_array);
	QJsonArray fileList_array;
	//QMessageBox::information(this, "rows", QString::number(ui.tableWidgetFiles->rowCount()));
	int rows = ui.tableWidgetFiles->rowCount();
	std::cout << "rows:" << rows << std::endl;
	boolean isHaveMainfilever = false; //是否存在文件InternetCafeCharge.exe
	for (int i = 0; i < ui.tableWidgetFiles->rowCount(); i++)
	{
		QJsonObject fileObj;
		fileObj.insert("name", ui.tableWidgetFiles->item(i, 0)->text());
		fileObj.insert("ver", ui.tableWidgetFiles->item(i, 1)->text());
		fileObj.insert("md5", ui.tableWidgetFiles->item(i, 2)->text());
		fileObj.insert("reg", ui.tableWidgetFiles->item(i, 3)->text());
		fileObj.insert("runorder", ui.tableWidgetFiles->item(i, 4)->text());
		fileObj.insert("run", ui.tableWidgetFiles->item(i, 5)->text());
		fileObj.insert("runparam", ui.tableWidgetFiles->item(i, 6)->text());
		fileObj.insert("dir", ui.tableWidgetFiles->item(i, 7)->text());
		fileObj.insert("protect", ui.tableWidgetFiles->item(i, 8)->text());
		fileList_array.push_back(fileObj);

		//mainfilever 设置InternetCafeCharge.exe文件的ver
		if (ui.tableWidgetFiles->item(i, 0)->text()=="InternetCafeCharge.exe")
		{
			isHaveMainfilever = true;
			mainfilever_save = ui.tableWidgetFiles->item(i, 1)->text();
			obj.insert("mainfilever", mainfilever_save);
		}

		//保存到fileList_save里
		FileStruct file;
		file.name = ui.tableWidgetFiles->item(i, 0)->text();
		file.ver = ui.tableWidgetFiles->item(i, 1)->text();
		file.md5 = ui.tableWidgetFiles->item(i, 2)->text();
		file.reg = ui.tableWidgetFiles->item(i, 3)->text();
		file.runorder = ui.tableWidgetFiles->item(i, 4)->text();
		file.run = ui.tableWidgetFiles->item(i, 5)->text();
		file.runparam = ui.tableWidgetFiles->item(i, 6)->text();
		file.dir = ui.tableWidgetFiles->item(i, 7)->text();
		file.protect = ui.tableWidgetFiles->item(i, 8)->text();
		fileList_save.push_back(file);
	}
	obj.insert("files", fileList_array);

	if (!isHaveMainfilever) {
		QMessageBox box;
		box.setText("Can't find file InternetCafeCharge.exe，mainfilever is "+ mainfilever_save+",continue?");
		box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		int code=box.exec();
		if (code == QMessageBox::Cancel)
			return;
	}

	QJsonDocument document;
	document.setObject(obj);
	QString saveResultStr = document.toJson();
	std::string gbk_saveResultStr = saveResultStr.toLocal8Bit();
	//***复制文件****************************************************************************
	/*
	1.首先遍历当前的表的数据，保存在变量fileList_array里。（未写入文件）

	2.遍历修改的文件，逐一复制文件。

	如果某一文件复制失败：

	遍历fileList_array，找到复制失败的文件的项；

	判断是否是新加项：

	    如果是不是新加项，则将该项替换成原来未修改的值；

	    如果是新加项，则将其删除；

	
	*/
	//
	for (int i = 0; i<fileToBeCopy_List.size(); i++)
	{
		if (!copyFile(fileToBeCopy_List.at(i)))
		{
			//如果复制失败，则保存失败,将package.json里的值恢复
			QFileInfo finfo(fileToBeCopy_List.at(i));
			QString fName = finfo.fileName();	
			//遍历当前获取的package.json的项
			for (int k=0;k<fileList_array.size();k++)
			{
				if (fName==fileList_array.at(k).toObject().value("name").toString()) 
				{
				     //找到对应的package.json里的项
					//判断是否是新加项
					bool isNew=true;
					for (int j=0;j<fileList.size();j++)
					{
						if (fName == fileList.at(j).name)
						{
							//如果是覆盖项
							isNew = false;
							QJsonObject fileObj;
							fileObj.insert("name", fileList.at(j).name);
							fileObj.insert("ver", fileList.at(j).ver);
							fileObj.insert("md5", fileList.at(j).md5);
							fileObj.insert("reg", fileList.at(j).reg);
							fileObj.insert("runorder", fileList.at(j).runorder);
							fileObj.insert("run", fileList.at(j).run);
							fileObj.insert("runparam", fileList.at(j).runparam);
							fileObj.insert("dir", fileList.at(j).dir);
							fileObj.insert("protect", fileList.at(j).protect);
							fileList_array.replace(k,fileObj);
						}

					}
					//如果是新加项，删除
					if (isNew)
					{
						fileList_array.removeAt(k);
					}
				}
			}

		}
	}

	//*******************************************************************************************
	
	
	QFile file(packageJsonPath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		QMessageBox::information(this, "", "file open fail!");
		return;
	}
	//加密 保存
	std::string saveResult_crypt = crypt.EnCrypt(gbk_saveResultStr, gbk_saveResultStr.length());
	QString a = QString::fromStdString(saveResult_crypt).toLocal8Bit();
	file.write(a.toStdString().data(), saveResult_crypt.length());
	file.close();
	//删除文件
	//deleteFiles(fileToBeDelete_List);
	//
	//将修改写入日志文件
	QFile logFile(QCoreApplication::applicationDirPath() + "/log.log");
	if (!logFile.open(QIODevice::ReadWrite))  //先读出之前的log
	{
		QMessageBox::information(this, "Waring:", "the log.txt open fail!");
		return;
	}
	std::string log_save = logFile.readAll();
	logFile.close();

	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))  //再写入现在的log
	{
		QMessageBox::information(this, "Waring:", "the log.txt open fail!");
		return;
	}
	logFile.write(getLogTxt().toLocal8Bit());
	logFile.close();
	if (!logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) //再写入之前的log
	{
		QMessageBox::information(this, "Waring:", "the log.txt open fail!");
		return;
	}
	logFile.write(log_save.data());
	logFile.close();

	this->close();
	emit exitSignal(1); //发送信号，关闭后打开
	QMessageBox::information(this, "", "Save success!");
}
//void JsonInfoWindow::onReceiveModifySignalSlot(QString fileName, QString action)
//{	
//	QDateTime dateTime = QDateTime::currentDateTime();
//	logText.append(dateTime.toString() + "\n");
//	QString changeTxt = fileName+"  "+action;
//	logText.append(changeTxt + "\n");
//	
//}
//显示日志
void JsonInfoWindow::showLogSlot()
{
	if (!QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/log.log")))
		QMessageBox::information(this, "", QDir::currentPath() + "/log.log open log fail!");
}
//打包
void JsonInfoWindow::packageSlot()
{	
	QDir appDir(QCoreApplication::applicationDirPath());
	if (!appDir.cdUp())
	{
		QMessageBox::information(this, "", "cant't find build.bat");
		return;
	}
	//*********************************************************************
	//读取版本号  形式 ：1.4.0.2(1526)
	QString versionName="";
	QFile ChangeFile(appDir.absolutePath() +"/Change.txt");
	if (!ChangeFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this,"","Change.txt open fail");
	}
	else {
		QTextStream in(&ChangeFile);
		int i = 0;
		while (!in.atEnd())
		{
			versionName = in.readLine();
			i++;
			if (i == 2)
			{
				break;
			}
		}
		versionName.replace("(","_");
		versionName=versionName.mid(0, versionName.length() - 1);
		versionName.prepend(" ");
		ChangeFile.close();
	}
	
	QMessageBox::information(this, "","VersionName is:"+versionName);
	//*******************************************************************

	
	QString path = appDir.dirName() + "/build.bat";
	//QMessageBox::information(this,"build.bat filePath",path);
	//bool b = process.startDetached(appDir.absolutePath()+"/build.bat");
	bool b = process.startDetached(appDir.absolutePath() + "/build.bat"+versionName);
	if (!b)
	{
		QMessageBox::information(this, "", "open build.bat fail! path="+ appDir.absolutePath() + "/build.bat");
	}

}
//上传
void JsonInfoWindow::uploadSlot()
{
	QDir appDir(QCoreApplication::applicationDirPath());
	bool b = process.startDetached(appDir.absolutePath()+"/ftp_upload.exe");
	if (!b)
	{
		QMessageBox::information(this, "", "start ftp_upload.exe fail!");
	}
	//QMessageBox::information(this, "", "upload success");

}
//一键打包
void JsonInfoWindow::AutoPackageSlot()
{
	//生成
	saveAllSlot();
	//打包
	packageSlot();
	//上传
	uploadSlot();
	//QMessageBox::information(this, "", "auto package success");
}

//--------------------------------对于经常添加的文件
//显示
void JsonInfoWindow::showUsedFilesSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/UsedFiles.ini", QSettings::IniFormat);
	setting->setIniCodec("UTF8");
	for (int i = 0; i < setting->allKeys().size(); i++)
	{
		//QString checkState = setting->allKeys().at(i);
		//QString filePath = setting->value(checkState).toString();
		//QMessageBox::information(NULL, "filePath:", filePath); //显示filePath
		QString value = setting->value(setting->allKeys().at(i)).toString();
		QString filePath = value.mid(0,value.indexOf("&"));
		QString checkState = value.mid(value.indexOf("&")+1,-1);
		QListWidgetItem *item = new QListWidgetItem();
		item->setText(filePath);
		if (checkState == "Checked")
			item->setCheckState(Qt::Checked);
		else
			item->setCheckState(Qt::Unchecked);
		ui.listWidgetShow->addItem(item);
	};
}
//添加
void JsonInfoWindow::addUsedFilesSlot()
{
	QString filePath = QFileDialog::getOpenFileName(this, "", QDir::currentPath());
	if (filePath.isEmpty()) return;
	//charge the dir is already in the list or not
	for (int i = 0; i < ui.listWidgetShow->count(); i++)
	{
		if (ui.listWidgetShow->item(i)->text() == filePath)
		{
			QMessageBox::information(this, "Waring:", filePath + " is already in the list");
			return;
		}

	}
	QListWidgetItem *item = new QListWidgetItem();
	item->setText(filePath);
	item->setCheckState(Qt::Checked);
	ui.listWidgetShow->addItem(item);
	//写入文件...
	/*QString checkState;
	if (item->checkState() == Qt::Checked)
		checkState = "Checked";
	else
		checkState = "UnChecked";
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/UsedFiles.ini", QSettings::IniFormat);
	setting->setValue("filePaths/" + filePath, checkState);
	delete setting;*/

}
//删除
void JsonInfoWindow::deleteUsedFilesSlot()
{
	//QMessageBox box(QMessageBox::Warning, "info", "Are you sure to delete the checked dirs?");
	//box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	//int ret = box.exec();
	//if (ret == QMessageBox::Cancel) return;
	for (int i = 0; i < ui.listWidgetShow->count(); i++)
	{
		QListWidgetItem *item = ui.listWidgetShow->item(i);
		if (item->isSelected())
		{
			QString filePath = item->text();
			//删除文件
			QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/UsedFiles.ini", QSettings::IniFormat);
			setting->remove(filePath);
			delete setting;
			delete item;
		}
	}
}

//导入
void JsonInfoWindow::copyTofilesSlot()
{
	QMessageBox box(QMessageBox::Warning, "info", "Are you sure to add checked files to file list?");
	box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	int ret = box.exec();
	if (ret == QMessageBox::Cancel) return;
	for (int i = 0; i < ui.listWidgetShow->count(); i++)
	{
		QListWidgetItem *item = ui.listWidgetShow->item(i);
		if (item->checkState() == Qt::Checked)
		{
			QString filePath = item->text();
			addFile(filePath);
		}
	}
}
//点击item函数
void JsonInfoWindow::onItemClickedSlot(QListWidgetItem *item)
{
	deleteItem = item;
}
//保存经常引入的文件打勾状态,在退出时调用
void JsonInfoWindow::saveUsedFileStateSlot()
{
	QSettings *setting = new QSettings(QCoreApplication::applicationDirPath() + "/UsedFiles.ini", QSettings::IniFormat);
	setting->clear();
	setting->setIniCodec("UTF8");
	for (int i = 0; i < ui.listWidgetShow->count(); i++)
	{
		QListWidgetItem *item = ui.listWidgetShow->item(i);
		//QMessageBox::information(NULL,"item value",item->text());
		QString checkState;
		if (item->checkState() == Qt::Checked)
			checkState = "Checked";
		else
			checkState = "UnChecked";
		QString filePath = item->text();
		//QMessageBox::information(NULL,"saveFilePath",filePath);  //显示保存的filePath
		setting->setValue(QString::number(i),item->text()+"&"+checkState);
	}

	delete setting;

	//用xml
	//QDomDocument doc;
	//QFile file(QCoreApplication::applicationDirPath()+"/UsedFiles.xml");
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	//{
	//	// QMessageBox::information(this,"Waring:","file open fail");
	//	QMessageBox::information(this,"","UsedFiles.xml open file");
	//	return;
	//}
	////    if(!doc.setContent(&file)){
	////        file.close();
	////        //QMessageBox::information(this,"Waring:","doc set fail");
	////        qDebug()<<"doc set fail";
	////        return 0;
	////    }
	//QDomElement root = doc.createElement("UsedFiles");
	//doc.appendChild(root);
	//for (int i = 0; i < ui.listWidgetShow->count(); i++)
	//{
	//	
	//	QDomElement file = doc.createElement("file");
	//	file.setAttribute("checkState",ui.listWidgetShow->item(i)->checkState());
	//	QDomText fileText = doc.createTextNode(ui.listWidgetShow->item(i)->text());
	//	file.appendChild(fileText);
	//	root.appendChild(file);
	//}
	//QTextStream out(&file);
	//doc.save(out, 4);
	//file.close();
}
//--------------------------------------------------
//*********************************************************
//***重写拖拽函数
void JsonInfoWindow::dragEnterEvent(QDragEnterEvent *e)
{
	if (e->mimeData()->hasFormat("text/uri-list"))
		e->accept();
}
//***重写松开拖拽函数
void JsonInfoWindow::dropEvent(QDropEvent *e)
{
	QList<QUrl> urls = e->mimeData()->urls();
	if (urls.isEmpty()) return;
	for (int i = 0; i < urls.size(); i++)
	{
		QString filePath = urls.at(i).toString();
		filePath = filePath.mid(8, filePath.length());
		addFile(filePath);
	}
}
//***重写退出时函数
void JsonInfoWindow::closeEvent(QCloseEvent *e)
{
	emit exitSignal(0);
	//保存经常引入的文件打勾状态
	saveUsedFileStateSlot();
}

