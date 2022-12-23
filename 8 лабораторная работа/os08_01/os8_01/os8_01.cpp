#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    time_t now = time(0);//возвращает количество секунд с 00:00 часов 1 января 1970 года по всемирному координированному времени
    tm ltm;
    localtime_s(&ltm, &now);//Преобразует значение времени в time_t структуру tm и исправляет местный часовой пояс
    cout << "date and time: " << ltm.tm_mday << "." << ltm.tm_mon + 1 << "." << ltm.tm_year + 1900 << " " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << endl;
}