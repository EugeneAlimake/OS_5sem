#include <Windows.h>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	LPCWSTR OS03_02_1= L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\3 лабораторная работа\\os03_02_1\\Debug\\os03_02_1.exe";//длинный указатель на постоянную строку
	LPCWSTR OS03_02_2= L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\3 лабораторная работа\\os03_02_2\\Debug\\os03_02_2.exe";
	STARTUPINFO si;//Структура STARTUPINFO используется функцией CreateProcess для того, чтобы определить оконный терминал, рабочий стол, стандартный дескриптор и внешний вид основного окна для нового процесса.
	PROCESS_INFORMATION pi;//Структура PROCESS_INFORMATION заполняется функцией CreateProcess с информацией о недавно созданном процессе и его первичном потоке.
	ZeroMemory(&si, sizeof(STARTUPINFO));// предназначена для обнуления памяти
	si.cb = sizeof(STARTUPINFO);

	if (CreateProcess(OS03_02_1//имя исполняемого модуля
		, NULL//командная строка
		, NULL//(дескриптор безопасности)
		, NULL//(дескриптор безопасности)
		, FALSE//дескриптор параметра наследования
		, CREATE_NEW_CONSOLE // флажки создания
		, NULL// новый блок конфигурации
		, NULL// имя текущего каталога
		, &si// информация предустановки
		, &pi // информация о процессе
	))
	{
		std::cout << "Дочерний процесс os03_02_1 создан \n";
	}
	else
	{
		std::cout << "Дочерний процесс os03_02_1 не создан\n";
	}

	if (CreateProcess(OS03_02_2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		std::cout << "Дочерний процесс os03_02_2 создан\n";
	}
	else
	{
		std::cout << "Дочерний процесс os03_02_2 не создан\n";
	}


	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 100; i++)
	{

		Sleep(1000);
		std::cout << "PID = " << pid << ":" << i << "\n";
	}

	WaitForSingleObject(pi.hProcess, INFINITE);//дождаться завершения потока, прежде чем продолжить выполнение других действий
	CloseHandle(pi.hProcess);//аннулирует заданный дескриптор объекта

	return 0;
}