/*Реализовать очередь с помощью двух стеков. Использовать
 * стек, реализованный с помощью динамического буфера.
Обрабатывать команды push back и pop front.*/

#include <iostream>
#include <malloc.h>

class Stack {
public:
    Stack(int Size);
    ~Stack();
    void Push(int value);
    int Pop();
    bool IsEmpty();

private:
    int* buffer;
    int buffer_Size;
    int top;
};

Stack::Stack(int Size) : buffer(new int[Size]), buffer_Size(Size), top(-1) {}

Stack::~Stack() {
    buffer = new int[0];
}

void Stack::Push(int value) {
    buffer[++top] = value;
}

bool Stack::IsEmpty() {
    return (top == -1);
}

int Stack::Pop() {
    if (top == -1) {
        return -1;
    }
    else {
        return buffer[top--];
    }
}

class Queue {
public:
    Queue(int Size);
    ~Queue();
    void Push(int value);
    int Pop();

private:
    Stack StackIn, StackOut;
};

Queue::Queue(int Size) : StackIn(Size), StackOut(Size) {}

Queue::~Queue() {
    StackIn.~Stack();
    StackOut.~Stack();
}

void Queue::Push(int value) {
    StackIn.Push(value);
}

int Queue::Pop() {
    if (!StackOut.IsEmpty()) {
        return StackOut.Pop();
    }
    else {
        while (!StackIn.IsEmpty()) {
            StackOut.Push(StackIn.Pop());
        }
        return StackOut.Pop();
    }
}

int main() {
    int n = 0;
    bool flag = true;
    std::cin >> n;

    Queue QueueIn(n);

    for (int i = 0; i < n; i++) {
        int command, value;
        std::cin >> command >> value;
        if (command == 3) {
            QueueIn.Push(value);
        }
        else {
            if (QueueIn.Pop() != value) {
                std::cout << "NO" << std::endl;
                flag = false;
            }
        }
    }

    if (flag) {
        std::cout << "YES" << std::endl;
    }

    //QueueIn.~Queue();

    return 0;
}