#include <string>
#include <iostream>

//reference: https://blog.csdn.net/fwb330198372/article/details/84637137
using namespace std;

int key[] = { 1,2,3,4,5,6,7};

void encryption(string& c, int key[]) {
	int len = c.size();
	for (int i = 0; i < len; i++) {
		c[i] = c[i] ^ key[i % 7];
	}
}
void decode(string& c, int key[]) {
	int len = c.size();
	for (int i = 0; i < len; i++) {
		c[i] = c[i] ^ key[i % 7];
	}
}

int main(int argc, char* argv[]) {
	std::string str = "hello world!";
	std::cout << "原文：" << str << std::endl;
	encryption(str, key);
	std::cout << "加密后密文：" << str << std::endl;
	decode(str, key);
	std::cout << "解密后密文：" << str << std::endl;
	return 0;
}
