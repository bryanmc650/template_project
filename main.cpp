#include <iostream>
#include "stack.hpp"

int main() {
    Stack<int> intStack(3);

    std::cout << "Pushing values...\n";
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Overflow test
    intStack.push(40); // Should print an overflow error

    std::cout << "Peeking top: " << intStack.peek() << std::endl;

    std::cout << "Popping values...\n";
    std::cout << "Popped: " << intStack.pop() << std::endl;
    std::cout << "Popped: " << intStack.pop() << std::endl;
    std::cout << "Popped: " << intStack.pop() << std::endl;

    // Underflow test
    std::cout << "Popped: " << intStack.pop() << std::endl; // Should print an underflow error

    return 0;
}
