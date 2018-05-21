// injectDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "functions.h"


void __cdecl Function::newPrint(DWORD arg1)
{
	printf("This is hooked print:%x! \n", arg1);
	//_origFunc* originalFunction = (_origFunc*)(base + 0x10B0);
	//originalFunction(arg1);
}

__int16 __stdcall Function::newCalcSpread()
{
	static DWORD _this, _ret;   //use static because it doesn't change registers
	__asm MOV _this,ECX

	//do pre-call stuff here
	/*
	__asm
	{
		MOV ECX, _this
		CALL [origFunc]
		MOV _ret,EAX
	}
	*/
	//do post-call stuff here

	__asm MOV ECX, _this
	//return _ret;   //if called origFunc, you can use this to return the return value of origiFunc
	return 0x0;
}

double __stdcall Function::newCalcRecoil()
{
	static DWORD _this, _ret;
	__asm MOV _this, ECX

	

	__asm MOV ECX, _this
	return (double)0.0;
}

void __stdcall Function::newAttackphy(DWORD a1, DWORD a2)
{
	static DWORD _this, _ret;   //use static because it doesn't change registers
	__asm MOV _this, ECX

	__asm MOV ECX, _this
	//return _ret;   //if called origFunc, you can use this to return the return value of origiFunc
}


