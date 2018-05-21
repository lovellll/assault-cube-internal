#pragma once

#include <Windows.h>
#include <iostream>
#include "offsets.h"
#include "hook.h"
#include "DebugConsole.h"

namespace Function
{

	void newPrint(DWORD arg1);

	__int16 __stdcall newCalcSpread();

	double __stdcall newCalcRecoil();

	void __stdcall newAttackphy(DWORD a1, DWORD a2);

	typedef void(__cdecl _origFunc)(DWORD arg1);

}

