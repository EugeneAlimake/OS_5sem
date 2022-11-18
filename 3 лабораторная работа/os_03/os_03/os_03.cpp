#include <Windows.h>
#include <iostream>
#include "windows.h"
#include "tlhelp32.h"
#include <iomanip>

int main()
{
	setlocale(LC_ALL, "Russian");
	DWORD pid = GetCurrentProcessId();
	//HANDLE - дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс.
	// Возвращает моментальный снимок данных текущих модулей, процессов, потоков и принадлежащих им куч памяти
	//снепшот — моментальный снимок, копия файлов и каталогов файловой системы на определённый момент времени.
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	PROCESSENTRY32 peProcessEntry;// Описывает структуру списка процессов, находящихся в адресном пространстве системы в момент снимка.
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(snap, &peProcessEntry))//Извлекает информацию о первом процессе снимка, полученного посредством CreateToolhelp32Snapshot
			throw L"Process32First";
		do
		{
			std::wcout << L"Name\t\t" << peProcessEntry.szExeFile << std::endl << L"PID\t\t" << peProcessEntry.th32ProcessID;
			if (peProcessEntry.th32ProcessID == pid)
				std::cout << " - выполняющийся процесс";
			std::wcout << L"\nParent ID\t" << peProcessEntry.th32ParentProcessID;

		} 
		while (Process32Next(snap, &peProcessEntry));//Соответственно извлекает информацию о следующем процессе

	system("pause");
	return 0;
}
