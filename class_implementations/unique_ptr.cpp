//
//  main.cpp
//  examq4
//
//  Created by qldo18 on 5/16/16.
//  Copyright (c) 2016 Qildo Inc. All rights reserved.
//

#include <iostream>
using namespace std;

template<typename T>
class UniquePtr {
    T* ptr = nullptr;
public:
    void bind(T* p) {
        if(ptr) {
            delete ptr;
        }
        ptr = p;
    }
    bool bound(void) const {
        return ptr != nullptr;
    }
    T& operator*(void) {
        return *ptr;
    }
    ~UniquePtr(void) {
        if(ptr) {
            delete ptr;
        }
    }
    UniquePtr(void) = default;
    UniquePtr(UniquePtr<T>& a) {
        ptr = a.ptr;
        a.ptr = nullptr;
    }
    UniquePtr(UniquePtr<T>&& a) :ptr(std::move(a.ptr)) {
        ptr = a.ptr;
    }
    UniquePtr operator=(UniquePtr<T>& arg) {
        this->ptr = arg.ptr;
        return *this;
    }
    UniquePtr operator=(UniquePtr<T>&& arg) {
        this->ptr = arg.ptr;
        return *this;
    }
};

int main(int argc, const char * argv[]) {
    UniquePtr<int> x;
    x = UniquePtr<int>{};
    x = x;
    x.bind(new int { 42} );
    UniquePtr<int> y {UniquePtr<int> { x } };
    if(x.bound()) {
        cout << "error\n";
    }
    cout << *y;
}
