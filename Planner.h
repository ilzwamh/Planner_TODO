#pragma once
#include "Stack.h"
#include "Task.h"
#include <fstream>
class Planner {
private:
    vector<Stack> Week;
    vector<string> Days = {"Понедельник", "Вторник", "Среда",      "Четверг",
                           "Пятница",     "Суббота", "Воскресенье"};

public:
    Planner() : Week(7) {}
    void LoadFromFile();
    void SaveToFile();
    void AddTask(int DayIndex, Task Task);
    void DeleteTask(int DayIndex, int TaskIndex);
    void CompleteTask(int DayIndex, int TaskIndex);
    void ChangePriority(int DayIndex, int TaskIndex, Prioritization Priority);
    void Menu();
    void WeekTasks();
    void WorkOfPlanner();
};
