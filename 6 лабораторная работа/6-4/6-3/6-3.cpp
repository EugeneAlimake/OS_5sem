#include <iostream>
#include <Windows.h>
using namespace std;

void sh(HANDLE pheap)
{
    PROCESS_HEAP_ENTRY phe; //Содержит сведения об элементе кучи
    phe.lpData = NULL;
    //указатель на блок в куче.
    ////Указатель на часть данных элемента кучи, Чтобы инициировать перечисление 
     // перемещение по куче от узла к узлу
    while (HeapWalk(pheap, &phe))
    {
        cout << "-- heap start adress = " << hex << phe.lpData
            << ", size = " << dec << phe.cbData
            << ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") // начало непрерывной области
            //Если PROCESS_HEAP_REGION используется в элементе wFlags , lpData указывает на первый виртуальный адресом
            << ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") // нераспределенная область
            << ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") // распределенная область
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

int main()
{
  
    HANDLE pheap = GetProcessHeap();  // получаем дескриптор встроенной (стандартной) кучи процесса
    std::cout << "--Before--\n\n";
    sh(pheap);

    // размещаем в ней массив на 300к интов
    int size = 300000;
    int* m = new int[size];
    cout << "adress = " << hex << m << ", size = " << dec << size << " \n\n";

    std::cout << "\n\n--After--\n\n";
    sh(pheap);
}
