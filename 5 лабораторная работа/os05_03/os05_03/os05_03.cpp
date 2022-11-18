#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <time.h>

using namespace std;

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
  
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS:         std::cout << " ----+ priority = IDLE_PRIORITY_CLASS"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS"; break;
    case NORMAL_PRIORITY_CLASS:       std::cout << " ----+ priority = NORMAL_PRIORITY_CLASS"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS"; break;
    case HIGH_PRIORITY_CLASS:         std::cout << " ----+ priority = HIGH_PRIORITY_CLASS"; break;
    case REALTIME_PRIORITY_CLASS:     std::cout << " ----+ priority = REALTIME_PRIORITY_CLASS"; break;
    default:                          std::cout << " ----+ priority = ?"; break;
    }
    return;
}

void printThreadPrty(HANDLE h)
{
    DWORD prty = GetThreadPriority(h);
    std::cout << "--ID: " << GetCurrentThreadId() << "\n";

    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST: std::cout << " ----+ priority = THREAD_PRIORITY_LOWEST"; break;
    case THREAD_PRIORITY_BELOW_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_BELOW_NORMAL"; break;
    case THREAD_PRIORITY_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_NORMAL"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_ABOVE_NORMAL"; break;
    case THREAD_PRIORITY_HIGHEST: std::cout << " ----+ priority = THREAD_PRIORITY_HIGHEST"; break;
    case THREAD_PRIORITY_IDLE: std::cout << " ----+ priority = THREAD_PRIORITY_IDLE"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " ----+ priority = THREAD_PRIORITY_TIME_CRITICAL"; break;
    default: std::cout << " ----+ priority = ?\n"; break;
    }
    return;
}

void SetProccesPriority(HANDLE hp, int priority)
{
    if (priority == 1)
    {
        SetPriorityClass(hp, IDLE_PRIORITY_CLASS);
    }
    if (priority == 2)
    {
        SetPriorityClass(hp, BELOW_NORMAL_PRIORITY_CLASS);
    }
    if (priority == 3)
    {
        SetPriorityClass(hp, NORMAL_PRIORITY_CLASS);
    }
    if (priority == 4)
    {
        SetPriorityClass(hp, ABOVE_NORMAL_PRIORITY_CLASS);
    }
    if (priority == 5)
    {
        SetPriorityClass(hp, HIGH_PRIORITY_CLASS);
    }
    if (priority == 6)
    {
        SetPriorityClass(hp, REALTIME_PRIORITY_CLASS);
    }
}

DWORD WINAPI TA()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);

    cout << endl << endl;
    double t1, t2;

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
            cout << ";\n Current processor = " << icpu << endl;
            cout << "-------------------------------------" << endl;
        }
    }

    cout << "\nTID: " << GetCurrentThreadId() << "has finished. Time:" << clock() - t1 << "ms." << endl << endl;

    return 0;
}

void SetPriorityThread(HANDLE hp, int priority)
{
    switch (priority)
    {
    case 1:
        SetThreadPriority(hp, THREAD_PRIORITY_IDLE);
        break;
    case 2:
        SetThreadPriority(hp, THREAD_PRIORITY_LOWEST);
        break;
    case 3:
        SetThreadPriority(hp, THREAD_PRIORITY_BELOW_NORMAL);
        break;
    case 4:
        SetThreadPriority(hp, THREAD_PRIORITY_NORMAL);
        break;
    case 5:
        SetThreadPriority(hp, THREAD_PRIORITY_ABOVE_NORMAL);
        break;
    case 6:
        SetThreadPriority(hp, THREAD_PRIORITY_HIGHEST);
        break;
    case 7:
        SetThreadPriority(hp, THREAD_PRIORITY_TIME_CRITICAL);
        break;
    default:
        SetPriorityClass(hp, THREAD_PRIORITY_NORMAL);
        break;
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    for (int i = 0; i < argc; i++)
    {
        cout << "arg" << i << ": " << argv[i] << "\n";
    }

    HANDLE hp = GetCurrentProcess();
    try
    {
        DWORD pa = NULL, sa = NULL;

        if (!GetProcessAffinityMask(hp, &pa, &sa))
            throw "GetProcessAffinityMask";

        cout << " Process Affinity Mask: " << showbase << hex << pa << "\n";
        cout << " System Affinity Mask: " << showbase << hex << sa << "\n";
        cout << dec << noshowbase << "\n\n";

        if (argv[1] != NULL) //целое число, задающее маску доступности процессоров (affinity mask);  
        {
            unsigned long long mask;
            sscanf_s(argv[1], "%d", &mask);

            if (!SetProcessAffinityMask(hp, mask))
                throw "SetProcessAffinityMask";

            if (!GetProcessAffinityMask(hp, &pa, &sa))
                throw "GetProcessAffinityMask";

            cout << " Process Affinity Mask: " << showbase << hex << pa << "\n";
            cout << " System Affinity Mask: " << showbase << hex << sa << "\n";
            cout << dec << noshowbase;


            if (argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
                //целое число, задающее класс приоритет процесса;
                //целое число, задающее  приоритет   первого, второго  дочернего потока
            {
                int priority = 0;
                sscanf_s(argv[2], "%d", &priority);
                SetProccesPriority(GetCurrentProcess(), priority);

                sscanf_s(argv[3], "%d", &priority);

                DWORD ChildId1 = NULL;
                HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId1);
                SetPriorityThread(hChild1, priority);
                ResumeThread(hChild1);

                sscanf_s(argv[4], "%d", &priority);

                DWORD ChildId2 = NULL;
                HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId2);
                SetPriorityThread(hChild2, priority);
                ResumeThread(hChild2);
            }
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << "\n";
    }


    system("pause");
}

