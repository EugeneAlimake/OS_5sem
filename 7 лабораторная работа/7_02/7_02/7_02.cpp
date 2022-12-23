#include <Windows.h>
#include <iostream>

using namespace std;

DWORD pid = NULL;

CRITICAL_SECTION cs;

void CriticalLoop(const char* threadName, DWORD tid)
{
	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);//только один поток одновременно может войти в критическую секцию
		}

		cout << threadName << " Thread: " << "tid-" << tid << ": " << i << "\n";
		Sleep(100);

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
			//чтобы освободить монопольное использование критической секции. 
		}
	}
}

DWORD WINAPI ChildThread_A()
{
	CriticalLoop("A", GetCurrentThreadId());
	return 0;
}

DWORD WINAPI ChildThread_B()
{
	CriticalLoop("B", GetCurrentThreadId());
	return 0;
}

void main()
{
	pid = GetCurrentProcessId();

	DWORD tid = GetCurrentThreadId();

	DWORD ChildA_Id = NULL;
	DWORD ChildB_Id = NULL;

	InitializeCriticalSection(&cs);

	HANDLE hChildA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_A, NULL, 0, &ChildA_Id);
	HANDLE hChildB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_B, NULL, 0, &ChildB_Id);

	CriticalLoop("Main", GetCurrentThreadId());

	WaitForSingleObject(hChildA, INFINITE);
	CloseHandle(hChildA);
	WaitForSingleObject(hChildB, INFINITE);
	CloseHandle(hChildB);

	DeleteCriticalSection(&cs);
}