#include "PackageJsonHelp.h"

PackageJsonHelp::PackageJsonHelp(QObject *parent)
	: QObject(parent)
{
}

PackageJsonHelp::~PackageJsonHelp()
{
}

//加密
std::string PackageJsonHelp::Encrypt(std::string S, unsigned short Key) // 加密函数
{
	S = S + "PC";
	std::string Result, str;
	size_t i, j;

	Result = S; // 初始化结果字符串
				// 依次对字符串中各字符进行操作
	for (i = 0; i < S.length(); i++)
	{
		Result.at(i) = S.at(i) ^ (Key >> 8); // 将密钥移位后与字符异或
		Key = ((unsigned char)Result.at(i) + Key)*C1 + C2; // 产生下一个密钥
	}
	S = Result; // 保存结果
	Result.clear(); // 清除结果
	for (i = 0; i < S.length(); i++) // 对加密结果进行转换
	{
		j = (unsigned char)S.at(i); // 提取字符
									// 将字符转换为两个字母保存
		str = "12"; // 设置str长度为2
		str.at(0) = 65 + j / 26;
		str.at(1) = 65 + j % 26;
		Result += str;
	}
	return Result;
}
//解密
std::string PackageJsonHelp::Decrypt(std::string S, unsigned short Key) // 解密函数
{
	std::string Result, str;
	size_t i, j;
	for (i = 0; i < S.size() / 2; i++) // 将字符串两个字母一组进行处理
	{
		j = ((unsigned char)S.at(2 * i) - 65) * 26;
		j += (unsigned char)S.at(2 * i + 1) - 65;
		str = "1"; // 设置str长度为1
		str.at(0) = j;
		Result += str; // 追加字符，还原字符串
	}
	S = Result; // 保存中间结果
	for (i = 0; i < S.size(); i++) // 依次对字符串中各字符进行操作
	{
		Result.at(i) = (unsigned char)S.at(i) ^ (Key >> 8); // 将密钥移位后与字符异或
		Key = ((unsigned char)S.at(i) + Key)*C1 + C2; // 产生下一个密钥
	}

	Result = Result.substr(0, Result.size() - 2);
	return Result;
}
//解密2 调用上一个解密函数
std::string PackageJsonHelp::DeCrpty(std::string sSrcText, int ilen)
{


	static unsigned short wordkey1 = 62153;
	static unsigned short wordkey2 = 42536;
	static unsigned short wordkey3 = 21354;

	std::string dst3 = Decrypt(sSrcText, wordkey3);
	std::string dst2 = Decrypt(dst3, wordkey2);
	std::string dst = Decrypt(dst2, wordkey1);

	return dst;
}
//加密2 调用上一个加密函数
std::string PackageJsonHelp::EnCrypt(std::string dst, int length)
{
	static unsigned short wordkey1 = 62153;
	static unsigned short wordkey2 = 42536;
	static unsigned short wordkey3 = 21354;
	std::string dst2 = Encrypt(dst, wordkey1);
	std::string dst3 = Encrypt(dst2, wordkey2);
	std::string sSrcText = Encrypt(dst3, wordkey3);
	char szText[4];
	//int i;
	//for (i = 0; i < sSrcText.length(); i++)
	//	szText[i] = sSrcText[i];
	//szText[i] = 0;
	return sSrcText;
}

//读json ，返回解密后的json
QString PackageJsonHelp::readJson(QString packageJsonPath)
{
	QFile *file = new QFile(packageJsonPath);
	if (!file->open(QIODevice::ReadOnly))
	{
		QMessageBox::information(NULL, "Waring", "file open fail");
		return NULL;
	}
	std::string jsonResult = file->readAll();
	//解密
	jsonResult =DeCrpty(jsonResult.c_str(), jsonResult.length());
	//转码
	//realJSonInfo = UTF8code->toUnicode(jsonResult.data());;//解密后的json
	QString realJsonInfo = QString::fromLocal8Bit(jsonResult.data());
	//realJSonInfo = UTF8code->fromUnicode(realJSonInfo.toStdString().data())
	//ui.textEditFile->setText(realJSonInfo);
	file->close();
	delete file;
	return realJsonInfo;
}
//解析json  ,返回文件的路径集合
QList<PackageJsonHelp::FileStruct> PackageJsonHelp::analysisJson(QString realJsonInfo)
{
	QList<FileStruct> fileList;

	QJsonDocument document = QJsonDocument::fromJson(realJsonInfo.toUtf8());
	QJsonObject obj = document.object();
	QJsonArray filesJson = obj["files"].toArray();
	for (int i = 0; i < filesJson.size(); i++)
	{
		FileStruct file;
		QJsonObject fileObj = filesJson.at(i).toObject();
		file.dir = fileObj["dir"].toString();
		file.name= fileObj["name"].toString();
		file.ver = fileObj["ver"].toString();
		file.md5 = fileObj["md5"].toString();
		fileList.push_back(file);
	}
	return fileList;
}

//解析json,得到updateid和mainFilever
PackageJsonHelp::PackageInfo PackageJsonHelp::analysisJsonForPackageInfo(QString realJsonInfo)
{
	PackageInfo packageInfo;
	QJsonDocument document = QJsonDocument::fromJson(realJsonInfo.toUtf8());
	QJsonObject obj = document.object();
	packageInfo.updateid= QString::number(obj["updateid"].toInt());
	packageInfo.mainFilever = obj["mainfilever"].toString();
	return packageInfo;
}