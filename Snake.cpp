#include "Planner.h"
#include "Windows.h"

int main() {
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Planner MyPlanner;
    MyPlanner.LoadFromFile();
    MyPlanner.WorkOfPlanner();
    cout << "\nРабота завершена. До свидания! \033[91m<3\033[0m\n";
    return 0;
}