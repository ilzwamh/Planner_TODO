#include "Node.h"
#include "Task.h"
#pragma once
class Stack {
private:
    Node* Head;

public:
    Stack() : Head(nullptr) {}
    void Add(Task& Text);
    void Pop(int Index);
    Task& GetTask(int Index);
    bool IsEmpty();
    int Size();
};
