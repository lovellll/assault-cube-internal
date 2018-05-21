#include "stdafx.h"
#include "D3D9Hook.h"
#include "hook.h"
#include "D3D9HookCallback.h"
#include "DebugConsole.h"

LPDIRECT3DDEVICE9 D3D9Hook::gameDevice = nullptr;
D3D9Hook* D3D9Hook::instance = nullptr;
bool D3D9Hook::hookReadyPre = false;
bool D3D9Hook::hookReady = false;

DWORD D3D9Hook::endSceneAddress = NULL;
unsigned char* D3D9Hook::originalAsm = nullptr;

void D3D9Hook::initialize()
{
	while (!GetModuleHandleA("d3d9.dll"))
		Sleep(10);

	D3D9Hook::endSceneAddress = this->locateOrigEndSceneAddres();
#ifdef DEBUG
	DebugConsole::ConsolePrint("endSceneAddress is %x\n", D3D9Hook::endSceneAddress);
#endif // DEBUG

	if (D3D9Hook::endSceneAddress)
		D3D9Hook::originalAsm = Hook::hookWithJump(D3D9Hook::endSceneAddress, (DWORD)&endSceneTrampoline);  //store original endScene() asm code

	//while (!D3D9Hook::hookReadyPre)               //??
	//	Sleep(10);

	D3D9Hook::hookReady = true;
}

//to get endScene vftable address
DWORD D3D9Hook::locateOrigEndSceneAddres()
{
	WNDCLASSEXA wc =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		DefWindowProc,
		0L,0L,
		GetModuleHandleA(NULL),
		NULL, NULL, NULL, NULL,
		"DX", NULL
	};

	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return 0;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	LPDIRECT3DDEVICE9 pd3dDevice;
	HRESULT res = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);

	if (FAILED(res))
		return 0;

	endSceneAddress = Memory::getVF((DWORD)pd3dDevice, 42);
	pD3D->Release();
	pd3dDevice->Release();
	DestroyWindow(hWnd);//release our d3d9 Device
	return endSceneAddress;

}

DWORD __stdcall D3D9Hook::reportInitEndScene(LPDIRECT3DDEVICE9 device)
{
	return D3D9Hook::getInstance()->initHookCallback(device);
}

DWORD D3D9Hook::initHookCallback(LPDIRECT3DDEVICE9 device)
{
	D3D9Hook::gameDevice = device;

#ifdef DEBUG
	DebugConsole::ConsolePrint("device address is %x\n", device);
	DebugConsole::ConsolePrint("endSceneAddress is %x\n", D3D9Hook::endSceneAddress);
#endif
	
	while(D3D9Hook::originalAsm==NULL){}
	Hook::unhookWithJump(D3D9Hook::endSceneAddress, originalAsm);

	//D3DXCreateFont

	//this->placeHooks();
	//D3D9Hook::hookReadyPre = true;

	return D3D9Hook::endSceneAddress;                   //return endSceneAddress so reportInitEndScene can put it in EAX
}

