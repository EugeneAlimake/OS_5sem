#include <Windows.h>
#include <iostream>
#include <bitset>

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h); //приоритет процесса
    //DWORD — 32-битное беззнаковое целое.
    std::cout << " ----- Current PID = " << GetCurrentProcessId() << " \n";
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS:         std::cout << " ----+ priority = IDLE_PRIORITY_CLASS \n"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS \n"; break;
    case NORMAL_PRIORITY_CLASS:       std::cout << " ----+ priority = NORMAL_PRIORITY_CLASS \n"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS \n"; break;
    case HIGH_PRIORITY_CLASS:         std::cout << " ----+ priority = HIGH_PRIORITY_CLASS \n"; break;
    case REALTIME_PRIORITY_CLASS:     std::cout << " ----+ priority = REALTIME_PRIORITY_CLASS \n"; break;
    default:                          std::cout << " ----+ priority = ? \n"; break;
    }
    return;
}

void printThreadPrty(HANDLE h)//приоритет потока
{
    DWORD icpu = SetThreadIdealProcessor(h // дескриптор потока
        , MAXIMUM_PROCESSORS// номер идеального процессора
    );//устанавливает предпочитаемый процессор для потока
        DWORD prty = GetThreadPriority(h);
        std::cout << " ---- Current Thread ID = " << GetCurrentThreadId() << "\n";
    // std::cout << " ----+ Processor = " << GetCurrentProcessorNumber() << " \n";//Функция возвращает текущий номер процессора.
        std::cout << " ----+ Processor = " << icpu << " \n";
        std::cout << " ----+ MAXProcessors = " << MAXIMUM_PROCESSORS << " \n";

    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST:        std::cout << " ----+ priority = THREAD_PRIORITY_LOWEST \n"; break;
    case THREAD_PRIORITY_BELOW_NORMAL:  std::cout << " ----+ priority = THREAD_PRIORITY_BELOW_NORMAL \n"; break;
    case THREAD_PRIORITY_NORMAL:        std::cout << " ----+ priority = THREAD_PRIORITY_NORMAL \n"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL:  std::cout << " ----+ priority = THREAD_PRIORITY_ABOVE_NORMAL \n"; break;
    case THREAD_PRIORITY_HIGHEST:       std::cout << " ----+ priority = THREAD_PRIORITY_HIGHEST \n"; break;
    case THREAD_PRIORITY_IDLE:          std::cout << " ----+ priority = THREAD_PRIORITY_IDLE \n"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " ----+ priority = THREAD_PRIORITY_TIME_CRITICAL \n"; break;
    default:                            std::cout << " ----+ priority = ? \n"; break;
    }
    return;
}

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    std::cout << " =====================OS05_01=======================\n";
    std::cout<< "PID = " << pid << ", TID = " << tid << " : " << "\n";//процесс и поток
    try
    {
        {
            DWORD pa = NULL, sa = NULL;
            if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";
            //Функция GetProcessAffinityMask извлекает маску родственного процесса для заданного 
            //процесса и системную маску родственности для системы
            std::bitset<8> pa_bits(pa); //числа в двоичном формате (например, bin). Если необходим двоичный вывод 
            //можно использовать трюк std::bitset:
            std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
            //showbase - Выводить индикатор основания   системы счисления
            std::cout << " Process Affinity Mask: " << pa_bits << "\n";
            std::bitset<8> sa_bits(sa);
           
            std::cout << " System Affinity Mask: " << std::showbase << sa << "\n";
            std::cout << " System Affinity Mask: " << sa_bits << "\n";
            std::cout << " Processor: " <<std::noshowbase<< sa_bits.count() << "\n";
        }
    }
    catch (char* msg) { std::cout << "Error " << msg << "\n"; }
    std::cout << std::dec << std::noshowbase;

    printProcessPrty(hp);//приоритет процесса
    printThreadPrty(ht);//приоритет  потока
    std::cout << "\n\n";

    std::cout << " =====================================================\n";
    system("pause");
    return 0;
}
