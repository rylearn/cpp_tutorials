
#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack();
    explicit Stack(size_t length);

    Stack(const Stack<T>& src);
    Stack<T>& operator=(const Stack<T>& src);

    ~Stack();
    size_t size() const;
    bool isEmpty() const;
    void clear();
    void push(const T& value);
    T pop();
    T peek() const;

private:
    void expand_stack_size();
    void deep_copy(const Stack<T>& src);
    static const size_t INIT_CAP = 0;
    T *array;
    size_t capacity;
    size_t length;
};

template <typename T>
Stack<T>::Stack() {
    capacity = INIT_CAP;
    array = new T[capacity];
    length = 0;
}

template <typename T>
Stack<T>::Stack(size_t length)
    :length(length), capacity(length)
{
    array = new T[length];
}

template <typename T>
Stack<T>::~Stack() {
    delete[] array;
}

template <typename T>
size_t Stack<T>::size() const {
    return length;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return length == 0;
}

template <typename T>
void Stack<T>::clear() {
    for (T& val : array) {
        val = T();
    }
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (length == capacity)
        expand_stack_size();
    array[length++] = value;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty())
        throw std::length_error("Attempted to pop empty stack");
    return array[--length];
}

template <typename T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        throw std::length_error("Attempting to peek empty stack");
    }
    return array[length - 1];
}

template <typename T>
void Stack<T>::deep_copy(const Stack<T>& src) {
    array = new T[src.size()];
    for (int i = 0; i < src.size(); ++i) {
        array[i] = src.array[i];
    }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& src)
    :length(src.length), capacity(src.capacity) {
    delete[] array; // might cause problems
    deep_copy(src);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& src) {
    if (this != &src) { // *this != src
        delete[] this->array;
        deep_copy(src);
    }
    return *this;
}

template <typename T>
void Stack<T>::expand_stack_size() {
    T* old_array = array;
    capacity *= 2;
    array = new T[capacity];
    for (int i = 0; i < length; ++i) {
        array[i] = old_array[i];
    }
    delete[] old_array;
}

#endif //_STACK_H
