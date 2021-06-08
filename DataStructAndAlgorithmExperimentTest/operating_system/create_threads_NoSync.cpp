// MultiThreads.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#include<cstdio>
#include<ctime>
#include<cstring>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <windows.h>
#include <stdio.h>

#define THREADNUM 3//Ïß³ÌÊý

HANDLE Mutex;


DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	CTime time = CTime::GetCurrentTime();
	CString s = time.Format("%A, %B %d, %Y");
	int len = s.GetLength();
	WaitForSingleObject(Mutex, INFINITE);
	for (int i = 0; i < len; i++)
		putchar(s.GetAt(i));
	int t = time.GetHour();
	putchar(' ');
	if (t < 12)
	{
		putchar('A');
	}
	else
	{
		putchar('P');
	}
	putchar('M');
	putchar('\n');
	ReleaseMutex(Mutex);
	return 0;
}
int main(int argc, char* argv[])
{
	DWORD dwThreadId[THREADNUM];
	HANDLE hThread[THREADNUM];
	Mutex = CreateMutex(NULL, false, NULL);
	for (int i = 0; i < THREADNUM; i++)
		hThread[i] = CreateThread(
			NULL,
			0,
			ThreadFunc,
			NULL,
			CREATE_SUSPENDED,
			&dwThreadId[i]);
	for (int i = 0; i < THREADNUM; i++)
		ResumeThread(hThread[i]);
	Sleep(500 * THREADNUM);
	return 0;
}