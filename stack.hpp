#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <typename T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:
    Stack(int size = 10) : capacity(size), top(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(T value) {
        if (top >= capacity - 1) {
            std::cerr << "Stack overflow\n";
            return;
        }
        data[++top] = value;
    }

    T pop() {
        if (top < 0) {
            std::cerr << "Stack underflow\n";
            return T();  // Return default-constructed object
        }
        return data[top--];
    }

    bool isEmpty() const {
        return top == -1;
    }
};

#endif // STACK_HPP
