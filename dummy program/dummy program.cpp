// dummy program.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

int main()
{

	int varInt = 123456;
	string varString = "DefaultString";
	char arrChar[128] = "Long char array right there ->";

	int* ptr2int = &varInt;
	int** ptr2ptr = &ptr2int;
	int*** ptr2ptr2 = &ptr2ptr;

	while (1)
	{
		cout << "Process ID: " << dec << GetCurrentProcessId() << endl << endl;

		cout << "varInt       " << &varInt << " = " << dec << varInt << endl;	
		cout << "varString    " << &varString << " = " << varString << endl;
		cout << "arrchar[128] " << (uintptr_t)arrChar << " = " << arrChar << endl << endl;

		cout << "ptr2int " << &ptr2int << " = " << ptr2int << endl;		
		cout << "ptr2int " << &ptr2ptr << " = " << ptr2ptr << endl;		
		cout << "ptr2int " << &ptr2ptr2 << " = " << ptr2ptr2 << endl;

		cout << "press Enter to print again" << endl << endl;
		getchar();
		cout << "---------------------------------------------------------------" << endl << endl;

	}



	
	
	
	
	return 0;
}

