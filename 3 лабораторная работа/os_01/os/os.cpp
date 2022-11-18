#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId(); //текущий процесс

	for (unsigned long long i = 0; i < 100000; i++)
	{
		std::cout << "PID = " << pid << ":" << i << "\n";
		Sleep(1000);
	}
	system("pause");
	return 0;

}