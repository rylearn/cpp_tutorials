
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Die;

class Die {
    uint32_t val;
public:
    Die() {
        val = 0;
    }
    Die(uint32_t x) {
        val = x;
    }
    Die(const Die& x) {
        this->val = x.val;
    }
    Die operator=(const Die& x){
        val = x.val;
        return *this;
    }
    Die operator+(Die& arg){
        Die x;
        x.val = this->val + arg.val;
        return x;
    }
    Die operator+(uint32_t arg){
        Die x;
        x.val = this->val + arg;
        return x;
    }
    uint32_t operator()() {
        return rand()%6;
    }/*
    void f() {
        uint32_t roll;
        Die basic_die = Die(6);
        roll = basic_die();
        auto die6 = basic_die + 1;
        roll = die6();
        auto dice = die6 + die6;
        roll = dice();
    }*/
};

int main(int argc, const char * argv[]) {
    time_t t;
    srand((unsigned) time(&t));
    
    uint32_t roll;
    Die basic_die = Die(6);
    roll = basic_die();
    auto die6 = basic_die + 1;
    roll = die6();
    auto dice = die6 + die6;
    roll = dice();
    
    return 0;
}
