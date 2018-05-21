#include "stdafx.h"
#include "hook.h"
#include "offsets.h"
#include "functions.h"

DWORD Memory::getPointAddress(DWORD weapon_baseOffset, const std::vector<DWORD> &offsets)
{
	if (baseAddr == NULL)  //baseAddr!
		return NULL;

	DWORD pointAddress = readMemory<DWORD>((LPVOID)(baseAddr + weapon_baseOffset)); //get base pointer address
	int level = offsets.size();
	if (offsets.size() != 0)
	{
		for (int i = 0; i < level; ++i)
		{
			if (i == level - 1)
			{
				return(pointAddress + offsets[i]);   //if it gets to last level, plus the offet and 
													 //will not take it as a pointer and go into it
			}
			pointAddress = readMemory<DWORD>((LPVOID)(pointAddress + offsets[i]));
		}
	}
	return pointAddress;
}

DWORD Memory::getVF(DWORD classInst, DWORD funcIndex)
{
	DWORD VFTable = readMemory<DWORD>((LPVOID)classInst);
	DWORD VFaddress = VFTable + funcIndex * sizeof(DWORD);
	return readMemory<DWORD>((LPVOID)VFaddress);
}


DWORD Hook::callHook(DWORD hookAt, DWORD newFunc)
{
	DWORD newOffset = newFunc - hookAt - 5;
	DWORD origOffset = Memory::readMemory<DWORD>((LPVOID)(hookAt + 1));
	Memory::writeMemory<DWORD>((LPVOID)(hookAt + 1), newOffset, false);

	return origOffset + hookAt + 5;   //origFunc address
}

//hook a vfunc and return original vfunc address
DWORD Hook::vfHook(DWORD classInst, DWORD funcIndex, DWORD newFunc)
{
	DWORD vfTable = Memory::readMemory<DWORD>((LPVOID)classInst);
	DWORD hookAt = vfTable + funcIndex * sizeof(DWORD);
	DWORD origFunc = Memory::readMemory<DWORD>((LPVOID)hookAt);
	Memory::writeMemory((LPVOID)hookAt, newFunc, TRUE);
	return origFunc;
}

//return assembly code at hookAt address, 0xE9 = JMP
unsigned char * Hook::hookWithJump(DWORD hookAt, DWORD newFunc)
{
	DWORD newOffset = newFunc - hookAt - 5;
	unsigned char* originalAsm = new unsigned char[5];
	for (int i = 0; i < 5; i++)
	{
		originalAsm[i] = Memory::readMemory<unsigned char>((LPVOID)(hookAt + i));
	}
	Memory::writeMemory<BYTE>((LPVOID)hookAt, 0xE9);
	Memory::writeMemory<DWORD>((LPVOID)(hookAt + 1), newOffset);
	return originalAsm;
}

void Hook::unhookWithJump(DWORD hookAt, unsigned char* originalAsm)
{
	Sleep(10);  //debug
	for (int i = 0; i < 5; i++)
	{
		Memory::writeMemory<BYTE>((LPVOID)(hookAt+i), originalAsm[i], false);
#ifdef DEBUG
		DebugConsole::ConsolePrint("writing original asm code %x at %x\n", originalAsm[i],hookAt);
#endif
	}
	delete[] originalAsm;
}

