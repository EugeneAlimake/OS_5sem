#include <iostream>
#include <ctime>
#include <Windows.h>
int check;

void InputCriticalSection()
{
	//Префикс lock, помещенный перед командой, устанавливает сигнал на линии LOCK системной шины и запрещает доступ к шине другим процессорам на время выполнения данной команды.
	//Команда BTS сохраняет значение бита, из первого операнда со смещением, указанным вторым операндом, во флаге CF, а затем устанавливает этот бит в 1.

	// нулевой бит переменной check ставиться в значение 1
	_asm
	{
	CriticalSection:
		lock bts check, 0;
		jc CriticalSection
	}
}

void LeaveCriticalSection()
{
	//Команда BTR сохраняет значение бита, из первого операнда со смещением, указанным вторым операндом, во флаге CF, а затем обнуляет этот бит.
	// нулевой бит переменной check ставиться в значение 0
	_asm lock btr check, 0
}
DWORD WINAPI CriticalLoop(const char* threadName, DWORD tid) {
	int pid = GetCurrentProcessId();

	for (int i = 0; i < 90; i++)
	{
		if (i == 20) {
			InputCriticalSection();
		}
		if (i == 60) {
			LeaveCriticalSection();
		}
		std::cout << threadName << " PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}


	return 0;
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
int main()
{
	DWORD ChildId_T1 = NULL;
	DWORD ChildId_T2 = NULL;
	
	HANDLE handleA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_A, NULL, 0, &ChildId_T1);
	HANDLE handleB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_B, NULL, 0, &ChildId_T1);
		WaitForSingleObject(handleA, INFINITE);
		CloseHandle(handleA);
		WaitForSingleObject(handleB, INFINITE);
		CloseHandle(handleB);
	system("pause");
	return 0;
}
