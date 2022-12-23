#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000

using namespace std;

int i = 0;

DWORD WINAPI ChildThread()
{
    clock_t t1 = clock();
    while (true)
    {
        clock_t t2 = clock();
        if ((t2 - t1) % 3000 == 0)
        {

            cout << "number after 3sec.: " << i << endl;
        }
        if ((t2 - t1) >= 15000)
        {
            cout << "end: " << i << endl;
            ExitProcess(0);
        }
    }
    return 0;
}

int main()
{
    long long it = -0 * SECOND;
    DWORD ChildId = 0;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, NULL, &ChildId);
    HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);//функция создает ожидающий таймер в занятом состоянии
    if (!SetWaitableTimer(timer, (LARGE_INTEGER*)&it, 3000, NULL, NULL, FALSE)) throw "Error SetWaitableTimer";//Активирует указанный таймер ожидания.
    clock_t t1 = clock();
    while (true)
    {
        WaitForSingleObject(timer, INFINITE);
        i++;
    }
}