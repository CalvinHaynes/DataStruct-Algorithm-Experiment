#include<stdio.h>
#include<windows.h>
int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(NULL,
		//"c:\\windows\\system32\\mspaint.exe",
		"qq.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("Create Process Failed!\n");
		return -1;
	}
	else {
		printf("Parent Hello World!\n");
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("Child Process Complete\n");
	printf("Child Process Running\n");
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}