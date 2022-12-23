#include <Windows.h>
#include <iostream>

using namespace std;

void CreateChildProcess(const char* procName, LPCWSTR& exePath, STARTUPINFO& startupAInfo, PROCESS_INFORMATION& procAInfo)
{
	ZeroMemory(&startupAInfo, sizeof(STARTUPINFO));
	startupAInfo.cb = sizeof(STARTUPINFO);

	if (CreateProcess(exePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupAInfo, &procAInfo))
	{
		cout << "proc " << procName << " - created\n";
	}
	else
	{
		cout << "proc " << procName << " - not created\n";
	}
}

void main()
{
	LPCWSTR exePath = L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\7 лабораторная работа\\7_04A\\Debug\\7_04A.exe";
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procAInfo, procBInfo;
	CreateChildProcess("A", exePath, startupInfo, procAInfo);
	CreateChildProcess("B", exePath, startupInfo, procBInfo);

	HANDLE hs = CreateSemaphore(NULL, 2, 2, L"OS07_semaphore");

	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}

		cout << "Parent process: " << "pid-" << GetCurrentProcessId() << ": " << i << "\n";
		Sleep(100);

		if (i == 60)
		{
			ReleaseSemaphore(hs, 1, 0);
		}

	}

	WaitForSingleObject(&procAInfo, INFINITE);
	CloseHandle(procAInfo.hProcess);

	WaitForSingleObject(&procBInfo, INFINITE);
	CloseHandle(procBInfo.hProcess);

	CloseHandle(hs);
}