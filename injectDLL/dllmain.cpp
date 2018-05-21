// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "functions.h"
#include "DebugConsole.h"
#include "hook.h"
#include "dllmain.h"
#include "D3D9Hook.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//printf("DLL attached!\n");
		auto thread = CreateThread(NULL, 0, &ATTACHED, NULL, 0, NULL);
		CloseHandle(thread);
		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH: 
		break;
	case DLL_PROCESS_DETACH:
		//printf("DLL detached!\n");
		auto thread1 = CreateThread(NULL, 0, &DETACHED, NULL, 0, NULL);
		CloseHandle(thread1);
		break;
	}
	return TRUE;
}

DWORD WINAPI ATTACHED(LPVOID lpParam)
{
#ifdef DEBUG
	DebugConsole::AttachConsole();
	DebugConsole::ConsolePrint("DLL injected!\n");
#endif

	baseAddr = (DWORD)GetModuleHandle(NULL);

	/*
	auto thread = CreateThread(NULL, 0, &hookLoop, NULL, 0, NULL);
	CloseHandle(thread);

	auto thread1 = CreateThread(NULL, 0, &memoryLoop, NULL, 0, NULL);
	CloseHandle(thread1);
	*/

	auto thread2 = CreateThread(NULL, 0, &D3D9HookLoop, NULL, 0, NULL);
	CloseHandle(thread2);

	return 1;
}

DWORD WINAPI DETACHED(LPVOID lpParam)
{

	return 1;
}

DWORD WINAPI memoryLoop(LPVOID lpParam)
{
	while (true)
	{
		Sleep(1);
		//DebugConsole::ConsolePrint("BASE: %x",baseAddr);
		//refresh address every 1sec
		DWORD magAddr = Memory::getPointAddress(weapon_baseOffset, WPN_CURRENT_MAG_OFFSETS);
		DWORD waitAddr = Memory::getPointAddress(weapon_baseOffset, WPN_CURRENT_WAIT_OFFSETS);
		DWORD isautoAddr = Memory::getPointAddress(weapon_baseOffset, WPN_CURRENT_ISAUTO_OFFSETS);
		DWORD delayAddr = Memory::getPointAddress(weapon_baseOffset, WPN_CURRENT_DELAY_OFFSETS);
		for (int i = 0; i < 4; ++i)
		{
			Memory::writeMemory<int>((LPVOID)magAddr, 20, TRUE);
			Memory::writeMemory<int>((LPVOID)waitAddr, 1, TRUE);
			Sleep(150);
		}
		Memory::writeMemory<bool>((LPVOID)isautoAddr, TRUE, TRUE);
		//Memory::writeMemory<int>((LPVOID)delayAddr, 10, TRUE);    //is related to damage
	}
}

DWORD WINAPI hookLoop(LPVOID lpParam)
{
	DWORD classInst_old = NULL;
	while (true)
	{
		DWORD classInst = Memory::getPointAddress(weapon_baseOffset, WPN_CURRENT_CLASS_OFFSETS);
		//check whether weapon was changed
		if (classInst != classInst_old)
		{
			//printf("The base is now: %x\n", base);
			//_origFunc* originalFunction = (_origFunc*)callHook((base + 0x1111), (DWORD)&newPrint);	
			//DWORD tempPointer = readMemory<DWORD>((LPVOID)(baseAddr + 0x0010F4F4));
			//DWORD classInst = readMemory<DWORD>((LPVOID)(tempPointer + 0x378));
			//DWORD pointSpredFunc = getPointAddress(weapon_baseOffset, weapon_class_assault_spreadFunc);
			//DWORD pointRecoilFunc = getPointAddress(weapon_baseOffset, weapon_class_assault_recoilFunc);
			DWORD origFunc_current_spread = Hook::vfHook(classInst, 1, (DWORD)&Function::newCalcSpread);     //hook spread func
			DWORD origFunc_current_recoil = Hook::vfHook(classInst, 2, (DWORD)&Function::newCalcRecoil);
			DWORD origFunc_current_attackphy = Hook::vfHook(classInst, 5, (DWORD)&Function::newAttackphy);

			classInst_old = classInst;
		}
	}
}

DWORD WINAPI D3D9HookLoop(LPVOID lpParam)
{
	while (true) {
		D3D9Hook::getInstance()->initialize();
		Sleep(3000);
	}
	

	return 1;
}
