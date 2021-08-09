#pragma once
#include <windows.h>

typedef LPVOID(WINAPI* _K32VirtualAlloc)(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD  flAllocationType,
	DWORD  flProtect
	);

typedef HRSRC(WINAPI* _K32FindResource)(
	HMODULE hModule,
	LPWSTR  lpName,
	LPWSTR  lpType
	);

typedef HGLOBAL(WINAPI* _K32LoadResource)(
	HMODULE hModule,
	HRSRC hResInfo
	);

typedef LPVOID(WINAPI* _K32LockResource)(
	HGLOBAL hResData
	);

typedef DWORD(WINAPI* _K32SizeofResource)(
	HMODULE hModule,
	HRSRC hResInfo
	);

