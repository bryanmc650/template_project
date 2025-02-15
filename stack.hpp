#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstdint>
#include <utility>  // For std::swap

template <typename T>
class Stack {
private:
    T* data;
    int top;
    uint32_t capacity;

    void ensureCapacity() {
        if (top >= static_cast<int>(capacity) - 1) {
            uint32_t newCapacity = capacity * 2;
            T* newData = new T[newCapacity];

            for (uint32_t i = 0; i < capacity; i++) {
                newData[i] = std::move(data[i]);  // Move instead of copy
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
            
            std::cout << "Stack resized to " << capacity << " elements\n";
        }
    }

public:
    Stack(uint32_t size = 10) : capacity(size), top(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    // Push for lvalues (copy)
    void push(const T& value) {
        ensureCapacity();
        data[++top] = value;  // Copy
    }

    // Push for rvalues (move)
    void push(T&& value) {
        ensureCapacity();
        data[++top] = std::move(value);  // Move instead of copy
    }

    T pop() {
        if (top < 0) {
            throw std::runtime_error("Stack underflow: Cannot pop from an empty stack");
        }
        return std::move(data[top--]);  // Move instead of copy
    }

    T peek() const {
        if (top < 0) {
            throw std::runtime_error("Stack is empty: No top element to peek");
        }
        return data[top];
    }

    uint32_t size() const {
        return static_cast<uint32_t>(top + 1);
    }

    bool isEmpty() const {
        return top == -1;
    }

    // Reverse stack in place
    void reverse() {
        for (int i = 0; i <= top / 2; i++) {
            std::swap(data[i], data[top - i]);  // Move-aware swap
        }
    }
};

#endif // STACK_HPP
