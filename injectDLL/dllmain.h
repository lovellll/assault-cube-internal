#pragma once

DWORD WINAPI ATTACHED(LPVOID lpParam);

DWORD WINAPI DETACHED(LPVOID lpParam);

DWORD WINAPI memoryLoop(LPVOID lpParam);

DWORD WINAPI hookLoop(LPVOID lpParam);

DWORD WINAPI D3D9HookLoop(LPVOID lpParam);

