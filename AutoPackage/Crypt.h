#pragma once
#define C1 52845
#define C2 22719
#include <string>

class Crypt
{
public:
	Crypt();
	~Crypt();

	std::string EnCrypt(std::string dst, int length); // ���ܺ��������ռ��ܺ�����														

	std::string DeCrpty(std::string szText, int ilen); // ���ܺ���(���ս��ܺ���)

private:
	std::string  Encrypt(std::string S, unsigned short Key); // ���ܺ���

	std::string Decrypt(std::string S, unsigned short Key); // ���ܺ���

};
