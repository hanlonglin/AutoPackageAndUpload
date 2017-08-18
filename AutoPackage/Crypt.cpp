#include "Crypt.h"



Crypt::Crypt()
{
}


Crypt::~Crypt()
{
}
//����
std::string Crypt::Encrypt(std::string S, unsigned short Key) // ���ܺ���
{
	S = S + "PC";
	std::string Result, str;
	size_t i, j;

	Result = S; // ��ʼ������ַ���
				// ���ζ��ַ����и��ַ����в���
	for (i = 0; i < S.length(); i++)
	{
		Result.at(i) = S.at(i) ^ (Key >> 8); // ����Կ��λ�����ַ����
		Key = ((unsigned char)Result.at(i) + Key)*C1 + C2; // ������һ����Կ
	}
	S = Result; // ������
	Result.clear(); // ������
	for (i = 0; i < S.length(); i++) // �Լ��ܽ������ת��
	{
		j = (unsigned char)S.at(i); // ��ȡ�ַ�
									// ���ַ�ת��Ϊ������ĸ����
		str = "12"; // ����str����Ϊ2
		str.at(0) = 65 + j / 26;
		str.at(1) = 65 + j % 26;
		Result += str;
	}
	return Result;
}
//����
std::string Crypt::Decrypt(std::string S, unsigned short Key) // ���ܺ���
{
	std::string Result, str;
	size_t i, j;
	for (i = 0; i < S.size() / 2; i++) // ���ַ���������ĸһ����д���
	{
		j = ((unsigned char)S.at(2 * i) - 65) * 26;
		j += (unsigned char)S.at(2 * i + 1) - 65;
		str = "1"; // ����str����Ϊ1
		str.at(0) = j;
		Result += str; // ׷���ַ�����ԭ�ַ���
	}
	S = Result; // �����м���
	for (i = 0; i < S.size(); i++) // ���ζ��ַ����и��ַ����в���
	{
		Result.at(i) = (unsigned char)S.at(i) ^ (Key >> 8); // ����Կ��λ�����ַ����
		Key = ((unsigned char)S.at(i) + Key)*C1 + C2; // ������һ����Կ
	}

	Result = Result.substr(0, Result.size() - 2);
	return Result;
}
//����2 ������һ�����ܺ���
std::string Crypt::DeCrpty(std::string sSrcText, int ilen)
{


	static unsigned short wordkey1 = 62153;
	static unsigned short wordkey2 = 42536;
	static unsigned short wordkey3 = 21354;

	std::string dst3 = Decrypt(sSrcText, wordkey3);
	std::string dst2 = Decrypt(dst3, wordkey2);
	std::string dst = Decrypt(dst2, wordkey1);

	return dst;
}
//����2 ������һ�����ܺ���
std::string Crypt::EnCrypt(std::string dst, int length)
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
