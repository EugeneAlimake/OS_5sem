#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace std;

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h); //приоритет процесса
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS:         std::cout << "IDLE_PRIORITY_CLASS"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << "BELOW_NORMAL_PRIORITY_CLASS"; break;
    case NORMAL_PRIORITY_CLASS:       std::cout << "NORMAL_PRIORITY_CLASS"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << "ABOVE_NORMAL_PRIORITY_CLASS"; break;
    case HIGH_PRIORITY_CLASS:         std::cout << "HIGH_PRIORITY_CLASS"; break;
    case REALTIME_PRIORITY_CLASS:     std::cout << "REALTIME_PRIORITY_CLASS"; break;
    default:                          std::cout << " priority = ?"; break;
    }
    return;
}

void printThreadPrty(HANDLE h)//приоритет потока
{
    DWORD prty = GetThreadPriority(h);

    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST: std::cout << "THREAD_PRIORITY_LOWEST"; break;
    case THREAD_PRIORITY_BELOW_NORMAL: std::cout << "THREAD_PRIORITY_BELOW_NORMAL"; break;
    case THREAD_PRIORITY_NORMAL: std::cout << "THREAD_PRIORITY_NORMAL"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << "THREAD_PRIORITY_ABOVE_NORMAL"; break;
    case THREAD_PRIORITY_HIGHEST: std::cout << " THREAD_PRIORITY_HIGHEST"; break;
    case THREAD_PRIORITY_IDLE: std::cout << "  THREAD_PRIORITY_IDLE"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " THREAD_PRIORITY_TIME_CRITICAL"; break;
    default: std::cout << " ----+ priority = ?"; break;
    }
    return;
}

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();
    DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);//устанавливает предпочитаемый процессор для потока

    double t1;

    t1 = clock();
    for (unsigned long i = 1; i <= 1000000; i++)
    {
        if (i % 1000 == 0)
        {
            Sleep(200);

            cout << i << ": PID = " << GetCurrentProcessId() << ";\n TID = " << GetCurrentThreadId() << ";\n Pprty class = ";
            printProcessPrty(hp);
            cout << ";\n Tprty = ";
            printThreadPrty(ht);
            //cout << ";\n Current processor = " << GetCurrentProcessorNumber() << endl;//номер назначенного процессора.  
            cout << ";\n Current processor = " << icpu << endl;
        }
    }

    cout << "time:" << clock() - t1 << "ms." << endl << endl;

    system("pause");
}
