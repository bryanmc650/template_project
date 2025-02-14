#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstdint>  // For uint32_t

template <typename T>
class Stack {
private:
    T* data;          // Array to store stack elements
    int top;          // Index of top element
    uint32_t capacity; // Max number of elements (using uint32_t)

public:
    Stack(uint32_t size = 10) : capacity(size), top(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(T value) {
        if (top >= static_cast<int>(capacity) - 1) {
            std::cerr << "Stack overflow: Cannot push " << value << " (stack is full)\n";
            return;
        }
        data[++top] = value;
    }

    T pop() {
        if (top < 0) {
            std::cerr << "Stack underflow: Cannot pop from an empty stack\n";
            return T();  // Return default-constructed object
        }
        return data[top--];
    }

    T peek() const {
        if (top < 0) {
            std::cerr << "Stack is empty: No top element to peek\n";
            return T();  // Return default-constructed object
        }
        return data[top];
    }

    uint32_t size() const {
        return static_cast<uint32_t>(top + 1);
    }

    bool isEmpty() const {
        return top == -1;
    }
};

#endif // STACK_HPP
