#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    LPCWSTR an1 = L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\7 лабораторная работа\\7_05A\\Debug\\7_05A.exe",
        an2 = L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\/Лабораторные_работы\\7 лабораторная работа\\7_05B\\Debug\\7_05B.exe";
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;
    ZeroMemory(&si1, sizeof(STARTUPINFO));
    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO);
    si2.cb = sizeof(STARTUPINFO);

    HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"OS07_event");

    if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
        cout << "Process OS07_05A created" << endl;
    else cout << "Process OS07_05A not created" << endl;

    if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
        cout << "Process OS07_05B created" << endl;
    else cout << "Process OS07_05B not created" << endl;

    DWORD pid = GetCurrentProcessId();
    LONG prevcount = 0;

    for (int i = 0; i < 90; i++)
    {
        if (i == 15) SetEvent(he);
        Sleep(100);
        cout << pid << " main " << i << endl;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);

    CloseHandle(he);
}