#include <iostream>
#include <vector>
#include "stack.hpp"

struct TestObject {
    int id;

    TestObject() : id(0) { std::cout << "Default constructor\n"; }
    TestObject(int x) : id(x) { std::cout << "Parameterized constructor: " << id << "\n"; }

    // Copy constructor
    TestObject(const TestObject& other) : id(other.id) { 
        std::cout << "Copy constructor: " << id << "\n"; 
    }

    // Copy assignment operator (fixes the error)
    TestObject& operator=(const TestObject& other) {
        std::cout << "Copy assignment operator: " << other.id << "\n";
        if (this != &other) {  // Self-assignment check
            id = other.id;
        }
        return *this;
    }

    // Move constructor
    TestObject(TestObject&& other) noexcept : id(other.id) { 
        std::cout << "Move constructor: " << id << "\n"; 
        other.id = -1;  // Indicate "moved-from" state
    }

    // Move assignment operator
    TestObject& operator=(TestObject&& other) noexcept {
        std::cout << "Move assignment operator: " << other.id << "\n";
        if (this != &other) {  // Self-assignment check
            id = other.id;
            other.id = -1;
        }
        return *this;
    }

    ~TestObject() { std::cout << "Destructor: " << id << "\n"; }
};



int main() {
    try {
        std::cout << "Creating an integer stack...\n";
        Stack<int> intStack(3);

        std::cout << "\nPushing values...\n";
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);

        std::cout << "\nAttempting to push beyond capacity...\n";
        intStack.push(40);  // Should trigger dynamic resizing

        std::cout << "\nPeeking at the top: " << intStack.peek() << "\n";
        std::cout << "Stack size: " << intStack.size() << "\n";

        std::cout << "\nReversing stack...\n";
        intStack.reverse();
        std::cout << "Popped after reversal: " << intStack.pop() << "\n";

        std::cout << "\nPopping remaining values...\n";
        while (!intStack.isEmpty()) {
            std::cout << "Popped: " << intStack.pop() << "\n";
        }

        std::cout << "\nAttempting to pop from empty stack (should throw exception)...\n";
        std::cout << "Popped: " << intStack.pop() << "\n";  // Should trigger exception

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    std::cout << "\n==============================\n";

    std::cout << "Creating a stack of custom objects...\n";
    Stack<TestObject> objStack(2);

    std::cout << "\nPushing objects...\n";
    objStack.push(TestObject(1));
    objStack.push(TestObject(2));

    std::cout << "\nForcing a resize by pushing another object...\n";
    objStack.push(TestObject(3));  // Should trigger dynamic resizing

    std::cout << "\nPopping objects...\n";
    while (!objStack.isEmpty()) {
        TestObject obj = objStack.pop();
        std::cout << "Popped object with id: " << obj.id << "\n";
    }

    //--------------------------------------------------------------//
    std::cout << "\n==============================\n";
    std::cout << "\nCreating a stack of std::vector<int>...\n";
    Stack<std::vector<int>> vecStack(2);

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    std::cout << "\nPushing vectors onto the stack...\n";
    vecStack.push(v1);             // Copy v1
    vecStack.push(std::move(v2));  // Move v2 (v2 is now empty)

    std::cout << "\nPopping vectors from the stack...\n";
    std::vector<int> poppedVec = vecStack.pop();  // Moves from stack to poppedVec

    std::cout << "Popped vector contains: ";
    for (int num : poppedVec) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "\nPeeking at the remaining vector in the stack...\n";
    std::vector<int> peekedVec = vecStack.peek();  // Peeking (not popping)
    
    std::cout << "Peeked vector contains: ";
    for (int num : peekedVec) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "\nPopping last vector...\n";
    vecStack.pop();  // Moves the remaining vector out

    std::cout << "\nAttempting to pop from an empty stack (should throw an exception)...\n";
    try {
        vecStack.pop();  // This should throw an exception
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
