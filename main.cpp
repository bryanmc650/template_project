#include <iostream>
#include "stack.hpp"

int main() {
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    
    std::cout << "Popped: " << intStack.pop() << std::endl;
    std::cout << "Popped: " << intStack.pop() << std::endl;
    
    Stack<std::string> stringStack(3);
    stringStack.push("Hello");
    stringStack.push("World");
    
    std::cout << "Popped: " << stringStack.pop() << std::endl;
    std::cout << "Popped: " << stringStack.pop() << std::endl;
    
    return 0;
}
