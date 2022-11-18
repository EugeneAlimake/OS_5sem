#include <Windows.h>
#include <iostream>

DWORD WINAPI ChildThreaId()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{

		std::cout << "PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI ChildThreaId_2()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{

		std::cout << "PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	DWORD ChildId_T1 = NULL;
	DWORD ChildId_T2 = NULL;
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreaId, NULL, 0, &ChildId_T1);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreaId_2, NULL, 0, &ChildId_T2);	
	for (int i = 1; i < 100; i++)
	{
		if (i == 20)
			SuspendThread(hChild);//приостанавливает работу заданного потока.
		if (i == 60)
			ResumeThread(hChild);//возобновлять выполнение задач(потоков)

		if (i == 40)
			SuspendThread(hChild2); //приостанавливает работу заданного потока.

		std::cout << "PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}

	ResumeThread(hChild2);

	WaitForSingleObject(hChild, INFINITE);//дождаться завершения потока, прежде чем продолжить выполнение других действий
	CloseHandle(hChild);//аннулирует заданный дескриптор объекта

	WaitForSingleObject(hChild2, INFINITE);//дождаться завершения потока, прежде чем продолжить выполнение других действий
	CloseHandle(hChild2);//аннулирует заданный дескриптор объекта

	system("pause");
	return 0;
}