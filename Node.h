#include <iostream>
#include <string>
#include "Task.h"
#pragma once
using namespace std;

class Node {
private:
    Task Data;
    Node* Next;

public:
    Node(Task Data) : Data(Data), Next(nullptr) {}
    Task& GetData() {
        return Data;
    }
    Node*& GetNext() {
        return Next;
    }
};
