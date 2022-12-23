#include <iostream>
#include <Windows.h>
using namespace std;

void sh(HANDLE pheap)
{
    PROCESS_HEAP_ENTRY phe; //Содержит сведения об элементе кучи
    phe.lpData = NULL;
    //указатель на блок в куче.
    //Указатель на часть данных элемента кучи, Чтобы инициировать перечисление 
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
    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE  //указатель на то, что куча не должна синхронизировать доступ
        | HEAP_ZERO_MEMORY//установить содержимое выделяемой памяти в 0
        ,  // атрибуты
        4096*1024,   // начальный размер
        0 * 1024    // конечный размер
    );

    sh(heap);

    int* m = (int*)HeapAlloc(heap,
        HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 
        300000 * sizeof(int)//Количество выделенных байтов
    );
    //Выделяет блок памяти из кучи. Выделенная память не перемещается.
    cout << "-- array pointer adress = " << hex << m << " \n\n";

    sh(heap);
}
