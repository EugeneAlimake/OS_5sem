#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId(); //текущий процесс

	for (unsigned long long i = 0; i < 50; i++)
	{
		Sleep(1000);
		std::cout << "PID = " << pid << ":" << i << "\n";
	}
	system("pause");
	return 0;

}