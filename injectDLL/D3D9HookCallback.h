#pragma once
#include "D3D9Hook.h"
#include "DebugConsole.h"

DWORD __declspec(naked) endSceneTrampoline()
{
	DebugConsole::ConsolePrint("Tramoline\n");
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x04]
		PUSH EAX                          
		CALL D3D9Hook::reportInitEndScene
		JMP EAX                          
	}
	//duplicate the EAX, because we will call 2 functions, other than one function
	//and [ESP+0x04] will be d3d9 device that game uses, so use EAX to be pushed in stack
	//EAX will be the original EndScene() function address, so jump into it directly 
}