
#include <iostream>
#include <cassert>
#include "stack.h"

void stack_test() {
    Stack<char> char_stack;
    assert(char_stack.size() == 0);
    assert(char_stack.isEmpty());

    char_stack.push('A');
    assert(!char_stack.isEmpty());
    assert(char_stack.size() == 1);
    assert(char_stack.peek() == 'A');

    char_stack.push('B');
    assert(char_stack.peek() == 'B');
    assert(char_stack.size() == 2);
    assert(char_stack.pop() == 'B');
    assert(char_stack.size() == 1);
    assert(char_stack.peek() == 'A');

    char_stack.push('C');
    assert(char_stack.size() == 2);
    assert(char_stack.pop() == 'C');
    assert(char_stack.peek() == 'A');
    assert(char_stack.pop() == 'A');
    assert(char_stack.size() == 0);

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        char_stack.push(ch);
    }
    assert(char_stack.size() == 26);

    for (char ch = 'Z'; ch >= 'A'; ch--) {
        assert(char_stack.pop() == ch);
    }
    assert(char_stack.isEmpty());

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        char_stack.push(ch);
    }
    assert(char_stack.size() == 26);
    char_stack.clear();
    assert(char_stack.size() == 0);
    char_stack.clear();
    assert(char_stack.size() == 0);

    std::cout << "Unit tests succeeded" << std::endl;
}

int main() {
    stack_test();
    return 0;
}
