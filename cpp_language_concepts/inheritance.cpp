
#include <iostream>
using namespace std;

class Base {
public:
    virtual void doit(void) {
        cout << "Base\n";
    }
    virtual void cloneHere(Base* x) const {
        new (x) Base{};
    }
    Base() {
        
    }
};

class Small : public Base {
public:
    virtual void doit(void) {
        cout << "Small\n";
    }
    virtual void cloneHere(Base* x) const {
        new (x) Small{};
    }
    Small() {
        
    }
};

class Big : public Base {
    int x;
public:
    virtual void doit(void) {
        cout << "Big\n";
    }
    virtual void cloneHere(Base* x) const {
        new (x) Big{};
    }
    Big() {
        
    }
};

class PolyArray {
    Big* ptr = (Big*) ::operator new (sizeof(Big)*5);
public:
    Base& get(int k) {
        return ptr[k];
    }
    void set(int k, Base const & obj) {
        Base* p = &ptr[k];
        p-> ~Base();
        obj.cloneHere(p);
    }
    PolyArray(void){
        for(int k = 0; k < 5; ++k) {
            new(ptr+k) Big{};
        }
    }
    ~PolyArray(void) {
        for(int k = 0; k < 5; ++k) {
            (ptr+k)->~Big();
        }
        ::operator delete(ptr);
    }
};

int main(int argc, const char * argv[]) {
    PolyArray array;
    
    array.set(0, Base{});
    array.set(1, Small{});
    array.set(2, Big{});
    array.set(3, Small{});
    
    for(int k = 0; k < 5; k+=1) {
        array.get(k).doit();
    }
}
