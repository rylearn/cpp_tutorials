//
//  main.cpp
//  cppIterators
//
//  Created by qldo18 on 4/27/16.
//  Copyright (c) 2016 Qildo Inc. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<int> sampVector;
    vector<int>::iterator vectorIterator;
    
    // Add some elements to myIntVector
    sampVector.push_back(1);
    sampVector.push_back(4);
    sampVector.push_back(8);
    
    for(vectorIterator = sampVector.begin(); vectorIterator != sampVector.end(); vectorIterator++)
    {
        cout<<*vectorIterator<<" " << endl;
        //Should output 1 4 8
    }
    
    cout << vectorIterator[0] << "sj" << endl;
    auto x = vectorIterator - vectorIterator;
    cout << typeid(x).name() << endl;
    cout << *vectorIterator << " " << endl;
    cout << typeid(vectorIterator).name() << endl;
    cout << typeid(vectorIterator).name() << endl;
    cout << typeid(sampVector).name() << endl;
    
    return 0;
}
