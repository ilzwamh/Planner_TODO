#include "Stack.h"

// Добавление задачи
void Stack::Add(Task& Text) { 
    Node* newNode = new Node(Text);
    if (!Head) {
        Head = newNode;
    }
    else {
        newNode->GetNext() = Head;
        Head = newNode;
    }
}

// Удаление задачи
void Stack::Pop(int Index) {
    if (Index == 0) {
        Node* Temp = Head;
        Head = Head->GetNext();
        delete Temp;
    }
    else {
        Node* Prev = nullptr;
        Node* Temp = Head;
        for (int i = 0; i < Index; i++) {
            Prev = Temp;
            Temp = Temp->GetNext();
        }
        Prev->GetNext() = Temp->GetNext();
        delete Temp;
    }
}

// Получение данных задачи
Task& Stack::GetTask(int Index) {
    Node* Temp = Head;
    for (int i = 0; i < Index; i++) {
        Temp = Temp->GetNext();
    }
    return Temp->GetData();
}

bool Stack::IsEmpty() {
    return Head == nullptr;
}

// Количество задач в дне
int Stack::Size() {
    int Count = 0;
    Node* Temp = Head;
    while (Temp) {
        Count++;
        Temp = Temp->GetNext();
    }
    return Count;
}