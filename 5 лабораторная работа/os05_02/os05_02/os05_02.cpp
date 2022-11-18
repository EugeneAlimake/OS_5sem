// os05_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <Windows.h>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

void CreateProccersWithPriority(LPCWSTR an, STARTUPINFO si, int priority)
{
    PROCESS_INFORMATION pi;//Структура PROCESS_INFORMATION заполняется функцией CreateProcess с информацией о недавно созданном процессе и его первичном потоке.
    if (priority == 1)
    {
        if (CreateProcess(an,//имя исполняемого модуля
            NULL, NULL, NULL, FALSE//дескриптор параметра наследования
            , CREATE_NEW_CONSOLE| IDLE_PRIORITY_CLASS, // флажки создания 
            NULL, NULL, &si,// информация предустановки
            &pi// информация о процессе
        ))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 2)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | BELOW_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 3)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 4)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | ABOVE_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 5)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 6)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | REALTIME_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    for (int i = 0; i < argc; i++)
    {
        cout << "arg" << i << ": " << argv[i] << endl;
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


        if (argv[1] != NULL)//целое число, задающее маску доступности процессоров 
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

            if (argv[2] != NULL && argv[3] != NULL)//целое число, задающее класс приоритета первого, второго дочернего процесса;
            {
                STARTUPINFO si;//Структура STARTUPINFO используется функцией CreateProcess для того, чтобы определить оконный терминал, рабочий стол, стандартный дескриптор и внешний вид основного окна для нового процесса.

                ZeroMemory(&si, sizeof(STARTUPINFO));// предназначена для обнуления памяти
                si.cb = sizeof(STARTUPINFO);

                unsigned long long priority;
                sscanf_s(argv[2], "%d", &priority);//строка, используемая для извлечения данных формат: строка, содержащая спецификатор(ы) типа

                CreateProccersWithPriority(L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\5 лабораторная работа\\os05_02x\\Debug\\os05_02x.exe", si, priority);

                sscanf_s(argv[3], "%d", &priority);

                ZeroMemory(&si, sizeof(STARTUPINFO));// предназначена для обнуления памяти
                si.cb = sizeof(STARTUPINFO);

                CreateProccersWithPriority(L"C:\\Users\\thesi\\Desktop\\5\\ОСИС\\Лабораторные_работы\\5 лабораторная работа\\os05_02x\\Debug\\os05_02x.exe", si, priority);
            }
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << "\n";
    }
}
