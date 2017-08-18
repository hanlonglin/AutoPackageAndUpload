#pragma once
#define C1 52845
#define C2 22719
#include <string>

class Crypt
{
public:
	Crypt();
	~Crypt();

	std::string EnCrypt(std::string dst, int length); // 加密函数（最终加密函数）														

	std::string DeCrpty(std::string szText, int ilen); // 解密函数(最终解密函数)

private:
	std::string  Encrypt(std::string S, unsigned short Key); // 加密函数

	std::string Decrypt(std::string S, unsigned short Key); // 解密函数

};
