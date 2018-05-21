#pragma once

#include "hook.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//typedef HRESULT(WINAPI* _endScene)(LPDIRECT3DDEVICE9 pDevice);

class D3D9Hook
{
public:
	static D3D9Hook* getInstance()
	{
		if (!D3D9Hook::instance)
			D3D9Hook::instance = new D3D9Hook;
		return D3D9Hook::instance;
	}

	static void deldeteInstance()
	{
		if (D3D9Hook::instance)
		{
			delete D3D9Hook::instance;
			D3D9Hook::instance = nullptr;
		}
	}
	void initialize();

	static DWORD __stdcall reportInitEndScene(LPDIRECT3DDEVICE9 device);

private:
	D3D9Hook() {}
	~D3D9Hook() {}

	static LPDIRECT3DDEVICE9 gameDevice;         //to store game's d3d9 device

	static D3D9Hook* instance;
	static bool hookReadyPre, hookReady;
	static DWORD endSceneAddress;
	
	static unsigned char* originalAsm;     //putting it in public allows Hook::unhookWithJump to deldete[] it

	DWORD locateOrigEndSceneAddres();
	DWORD initHookCallback(LPDIRECT3DDEVICE9 device);
};
