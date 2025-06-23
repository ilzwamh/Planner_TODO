#include "Planner.h"

void Planner::LoadFromFile() {
    ifstream File("Tasks.txt");
    if (!File.is_open()) {
        cout << "\033[91mОшибка чтения файла!\033[0m\nИсправьте файл и возвращайтесь!";
        exit(1);
    }
    int Day;
    string Description;
    int Priority;
    bool IsCompleted;
    char Divider;
    while (File >> Day >> Divider && getline(File, Description, ';') &&
           File >> Priority >> Divider >> IsCompleted) {
        if (Day >= 0 && Day < 7) {
            Task task(Description, static_cast<Prioritization>(Priority));
            task.GetCompleted() = IsCompleted;
            Week[Day].Add(task);
        }
    }
    File.close();
}

void Planner::SaveToFile() {
    fstream File("Tasks.txt");
    if (!File.is_open()) {
        cout << "\033[91mОшибка файла для записи!\033[0m\nИсправьте файл и возвращайтесь!";
        exit(1);
    }
    for (int Day = 0; Day < 7; Day++) {
        Stack& Tasks = Week[Day];
        for (int i = 0; i < Tasks.Size(); i++) {
            Task& CurTask = Tasks.GetTask(i);
            File << Day << ';' << CurTask.GetDescription() << ';'
                 << static_cast<int>(CurTask.GetPriority()) << ';' << CurTask.GetCompleted()
                 << '\n';
        }
    }
    File.close();
}

void Planner::AddTask(int DayIndex, Task Task) {
    Week[DayIndex].Add(Task);
    SaveToFile();
}

void Planner::DeleteTask(int DayIndex, int TaskIndex) {
    Week[DayIndex].Pop(TaskIndex);
    SaveToFile();
}

void Planner::CompleteTask(int DayIndex, int TaskIndex) {
    Task& Temp = Week[DayIndex].GetTask(TaskIndex);
    Temp.GetCompleted() = !Temp.GetCompleted();
    SaveToFile();
}

void Planner::ChangePriority(int DayIndex, int TaskIndex, Prioritization Priority) {
    Task& Temp = Week[DayIndex].GetTask(TaskIndex);
    Temp.GetPriority() = Priority;
    SaveToFile();
}

void Planner::Menu() {
    cout << "\n\033[33m===\033[0m \033[93mПЛАНЕР 'TODO'\033[0m \033[33m===\033[0m\n";
    cout << "1. Показать все задачи\n";
    cout << "2. Добавить задачу\n";
    cout << "3. Удалить задачу\n";
    cout << "4. Отметить выполнение\n";
    cout << "5. Изменить приоритет\n";
    cout << "6. Выход\n";
    cout << "\033[33m====================\033[0m\n";
}

void Planner::WeekTasks() {
    cout << "\n\033[33m===\033[0m \033[93mВСЕ ЗАДАЧИ НА НЕДЕЛЮ\033[0m \033[33m===\033[0m\n";
    for (int i = 0; i < 7; i++) {
        cout << "\n\033[33m---\033[0m " << Days[i] << " \033[33m---\033[0m\n";
        Stack& Tasks = Week[i];
        if (Tasks.IsEmpty()) {
            cout << "   Нет задач\n";
        }

        for (int i = 0; i < Tasks.Size(); i++) {
            Task& CurTask = Tasks.GetTask(i);
            string IsCompleted;
            if (CurTask.GetCompleted()) {
                IsCompleted = "[\033[92mX\033[0m]";
            }
            else {
                IsCompleted = "[ ]";
            }
            string Priority;
            switch (CurTask.GetPriority()) {
            case Low:
                Priority = "\033[32mНизкий\033[0m";
                break;
            case Medium:
                Priority = "\033[33mСредний\033[0m";
                break;
            case High:
                Priority = "\033[91mВысокий\033[0m";
                break;
            }
            cout << "  " << i + 1 << ". " << IsCompleted << " " << CurTask.GetDescription() << " ("
                 << Priority << ")\n";
        }
    }
    cout << "\033[33m============================\033[0m\n";
}

// Основная работа планера
void Planner::WorkOfPlanner() {
    int Choice;
    while (true) {
        Menu();
        cout << "\033[96m> Выберите действие: \033[0m";
        cin >> Choice;
        while (Choice < 1 || Choice > 6 || cin.fail()) {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Menu();
            cout << "\033[91mОшибка ввода!\033[0m\n> Попробуйте еще раз: ";
            cin >> Choice;
        }
        system("cls");

        // Выход из планера
        if (Choice == 6) {
            break;
        }

        // Все задачи на неделю
        if (Choice == 1) {
            system("cls");
            WeekTasks();
            cout << "\n\033[96m> Выйти в меню - 0: \033[0m";
            int TempChoice;
            while (!(cin >> TempChoice) || TempChoice != 0) {
                system("cls");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                WeekTasks();
                cout << "\033[91mОшибка ввода!\033[0m\n> Введите 0 для выхода: ";
            }
            system("cls");
            continue;
        }

        int Day;
        cout << "\n\033[33m---\033[0m\033[93mВыберите день (0 - выход в меню):\033[0m\n";
        for (int i = 0; i < 7; ++i) {
            cout << i + 1 << ". " << Days[i] << endl;
        }
        cout << "\033[96m> Введите номер дня: \033[0m";

        while (!(cin >> Day) || Day < 0 || Day > 7) {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\033[33m---\033[0m\033[93mВыберите день (0 - выход в меню):\033[0m\n";
            for (int i = 0; i < 7; ++i) {
                cout << i + 1 << ". " << Days[i] << endl;
            }
            cout << "\033[91mОшибка ввода!\033[0m\n> Попробуйте еще раз: ";
        }
        if (Day == 0) {
            system("cls");
            continue;
        }

        Day--;
        system("cls");
        cout << "\n\033[33m---\033[0m " << Days[Day] << " \033[33m---\033[0m\n";
        Stack& Tasks = Week[Day];
        if (Tasks.IsEmpty()) {
            cout << "  Нет задач\n";
        }
        else {
            for (int i = 0; i < Tasks.Size(); i++) {
                Task& CurTask = Tasks.GetTask(i);
                string IsCompleted = CurTask.GetCompleted() ? "[\033[92mX\033[0m]" : "[ ]";
                string TaskPriority;
                switch (CurTask.GetPriority()) {
                case Low:
                    TaskPriority = "\033[32mНизкий\033[0m";
                    break;
                case Medium:
                    TaskPriority = "\033[33mСредний\033[0m";
                    break;
                case High:
                    TaskPriority = "\033[91mВысокий\033[0m";
                    break;
                }
                cout << "  " << i + 1 << ". " << IsCompleted << " " << CurTask.GetDescription()
                     << " (" << TaskPriority << ")\n";
            }
        }

        string Description;
        int Priority;
        int TaskIndex;

        switch (Choice) {
        case 2: // Добавление задачи
            cin.ignore();
            cout << "\033[96m> Введите описание задачи (0 - отмена): \033[0m";
            getline(cin, Description);
            if (Description == "0") {
                system("cls");
                break;
            }

            while (true) {
                cout << "\033[96m> Введите приоритет\033[0m (1 - \033[32mНизкий\033[0m, 2 - "
                        "\033[33mСредний\033[0m, 3 - \033[91mВысокий\033[0m, 0 - отмена): "
                        "\033[0m";
                if (!(cin >> Priority) || Priority < 0 || Priority > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\033[91mОшибка ввода!\033[0m\n";
                    continue;
                }
                if (Priority == 0) {
                    break;
                }
                if (Priority >= 1 && Priority <= 3) {
                    AddTask(Day, Task(Description, static_cast<Prioritization>(Priority - 1)));
                    break;
                }
            }
            system("cls");
            break;

        case 3: // Удаление задачи
            while (true) {
                cout << "\033[96m> Введите номер задачи для удаления (0-отмена): \033[0m";
                if (!(cin >> TaskIndex) || TaskIndex < 0 || TaskIndex > Tasks.Size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\033[91mОшибка ввода!\033[0m\n";
                    continue;
                }
                if (TaskIndex == 0) {
                    break;
                }
                if (TaskIndex >= 1 && TaskIndex <= Tasks.Size()) {
                    DeleteTask(Day, TaskIndex - 1);
                    break;
                }
            }
            system("cls");
            break;

        case 4: // Отметка выполнения
            while (true) {
                cout << "\033[96m> Введите номер задачи (0-отмена): \033[0m";
                if (!(cin >> TaskIndex) || TaskIndex < 0 || TaskIndex > Tasks.Size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\033[91mОшибка ввода!\033[0m\n";
                    continue;
                }
                if (TaskIndex == 0) {
                    break;
                }
                if (TaskIndex >= 1 && TaskIndex <= Tasks.Size()) {
                    CompleteTask(Day, TaskIndex - 1);
                    break;
                }
            }
            system("cls");
            break;

        case 5: // Изменение приоритета
            while (true) {
                cout << "\033[96m> Введите номер задачи (0-отмена): \033[0m";
                if (!(cin >> TaskIndex) || TaskIndex < 0 || TaskIndex > Tasks.Size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\033[91mОшибка ввода!\033[0m\n";
                    continue;
                }
                if (TaskIndex == 0) {
                    break;
                }

                int NewPriority;
                while (true) {
                    cout << "\033[96m> Введите новый приоритет\033[0m (1 - \033[32mНизкий\033[0m, 2 - "
                        "\033[33mСредний\033[0m, 3 - \033[91mВысокий\033[0m, 0 - отмена): \033[0m";
                    if (!(cin >> NewPriority)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[91mОшибка ввода!\033[0m\n";
                        continue;
                    }
                    if (NewPriority == 0) {
                        break;
                    }
                    if (NewPriority >= 1 && NewPriority <= 3) {
                        ChangePriority(Day, TaskIndex - 1,
                                       static_cast<Prioritization>(NewPriority - 1));
                        break;
                    }
                    cout << "\033[91mНеверный приоритет!\033[0m\n";
                }
                break;
            }
            system("cls");
            break;
        }
    }
}
