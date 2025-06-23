#include <iostream>
#include <string>
#include <vector>

#pragma once
using namespace std;

enum Prioritization {
    Low, Medium, High
};

class Task {
private:
    string Description;
    Prioritization Priority;
    bool IsCompleted;

public:
    Task(string Description = "", Prioritization Priority = Low, bool IsCompleted = false)
        : Description(Description), Priority(Priority), IsCompleted(false) {}
    string GetDescription() {
        return Description;
    }
    Prioritization& GetPriority() {
        return Priority;
    }
    bool& GetCompleted() {
        return IsCompleted;
    }
};
