#include <iostream>
#include <Windows.h>

using namespace std;
#define KB (1024)
#define PG (4096)
int pg = 256;


void saymem() {
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    std::cout << " -- Физическая память: " << ms.dwTotalPhys / KB << '\n';
    std::cout << " -- Доступно физ памяти: " << ms.dwAvailPhys / KB << '\n';
    std::cout << " -- Объем виртуальной памяти: " << ms.dwTotalVirtual / KB << '\n';
    std::cout << " -- Доступно виртуальной памяти: " << ms.dwAvailVirtual / KB << '\n';
}

int main()
{
    setlocale(LC_ALL, "rus");

    int memory_size;
    int page_size;
 
    // заполнение структуры информацией о системе
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    saymem();

    page_size = system_info.dwPageSize;
    memory_size = PG * page_size;
  
    // выделение виртуальной памяти 
    //без базового адреса, размер, 
    //Выполняется выделение страниц памяти для непосредственной работы с ними(при этом страницы заполняются нулями), 
    //типа доступа (чтение и запись))
    int* virtArray = (int*)VirtualAlloc(NULL,memory_size, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < memory_size / sizeof(int); i++)
    {
        virtArray[i] = i;
    }
   
    int char1 = 0xcd;
    int char2 = 0xc8;
    int char3 = 0xca;
    int index = (char1 * PG + ((char2 << 4) | (char3 >> 4)));
    std::cout << std::hex << virtArray[index] << std::endl;


    cout << endl;

    saymem();


    // освобождение выделенной памяти (адрес памяти, размер (при MEM_RELEASE здесь NULL), операция (освобождена))
    VirtualFree(virtArray, NULL, MEM_RELEASE) ? std::cout << "VirtualFree free\n" : std::cout << "Virtual false\n";
    saymem();

    //Н=205=CD
    //И=200=С8
    //К=202=СA
    //страница CD = 205
    //смещение С8С = 3212
    //адрес=4096*205=839680(10)=0х000CD000-first byte of 205's page
    //смещение 0x00000С8С=>3212
    //(839680+3212)/4 (sizeof(int) = 4)=210723=33723(16)
       //0x000CDС8С
}
