// os04-01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId(); //текущий процесс
	DWORD tid = GetCurrentThreadId(); //текущий поток
	unsigned long long d = MAXULONGLONG / 10000000;

	for (unsigned long long i = 0; i < MAXULONGLONG; i++)
	{
		std::cout << "PID = " << pid <<",  TID = "<<tid<< ":" << i << "\n";
		Sleep(1000);
	}
	system("pause");
	return 0;

}