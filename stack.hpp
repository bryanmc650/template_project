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
            // Resize: Double the capacity
            uint32_t newCapacity = capacity * 2;
            T* newData = new T[newCapacity];
    
            // Copy old data
            for (uint32_t i = 0; i < capacity; i++) {
                newData[i] = std::move(data[i]);
            }
    
            delete[] data;  // Free old memory
            data = newData;
            capacity = newCapacity;
            
            std::cout << "Stack resized to " << capacity << " elements\n";
        }
    
        data[++top] = value;
    }
    

    T pop() {
        if (top < 0) {
            throw std::runtime_error("Stack underflow: Cannot pop from an empty stack");
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

    void reverse() {
        for (int i = 0; i <= top / 2; i++) {
            std::swap(data[i], data[top - i]);
        }
    }  

    uint32_t size() const {
        return static_cast<uint32_t>(top + 1);
    }

    bool isEmpty() const {
        return top == -1;
    }
};

#endif // STACK_HPP
