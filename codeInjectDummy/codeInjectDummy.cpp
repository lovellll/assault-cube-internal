// codeInjectDummy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <Windows.h>

void print(DWORD outputv)
{
	std::cout << "the value is " << std::hex << outputv << std::endl;
}

int main()
{
	DWORD outv = 0x010F;
	getchar();
	
	print(outv);
	
	std::cout << "some assistant: " << std::endl
		<< "function address: " << &print << std::endl
		<< "var address: " << &outv << std::endl;

	getchar();
    return 0;
}

