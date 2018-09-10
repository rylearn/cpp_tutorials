//
//  main.cpp
//  exam1q6
//
//  Created by qldo18 on 5/16/16.
//  Copyright (c) 2016 Qildo Inc. All rights reserved.
//

#include <iostream>
using namespace std;

class Foo {
public:
    Foo(void) {
        cout << "default construct\n";
    }
    Foo(Foo const& rhs) {
        cout << "copy construct\n";
    }
    Foo(Foo&& rhs) {
        cout << "move construct\n";
    }
    ~Foo(void) {
        cout << "destruct\n";
    }
};

void doit(Foo param) {
    
}

int main(int argc, const char * argv[]) {
    Foo local{};
    doit(local);
    doit(Foo{});
}
