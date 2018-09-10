
#include <iostream>
using namespace std;

class Foo {
    int x;
    int y;
    void test(void) {}
    void test(void) {}
    virtual void doit(void) {}
    virtual void hi(void) {}
    virtual void hi2(void) {}
};

class Foo2 {
    
};

template <typename T>
class Base : T {
    virtual void doit(void) = 0;
};


//template<bool B, bool T>
//using Enable_if = typename std::enable_if<B, T>;
template <typename T>
class VirtChecker {
public:
    
    //Enable_if<std::is_class<T>::value,bool>
    bool virtCheck(void) {
        if(sizeof(Base<T>)==sizeof(T)) {
            return true;
        }
        else {
            return false;
        }
    }
    
    virtual void doit(void) {
        std::cout << "done";
    }
};

int main(int argc, const char * argv[]) {
    VirtChecker<Foo> y;
    std::cout << std::boolalpha << y.virtCheck() << std::endl;
    VirtChecker<Foo2> y2;
    std::cout << std::boolalpha << y2.virtCheck() << std::endl;
    //VirtChecker<int> y3;
    //std::cout << std::boolalpha << y3.virtCheck() << std::endl;
    return 0;
}
