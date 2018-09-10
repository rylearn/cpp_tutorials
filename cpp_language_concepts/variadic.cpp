
#include <iostream>
using namespace std;

//template<typename ...Args>
//void print(Args... args) {
//    for(int i = 0; i < num_of(args); ++i) {
//        cout << args[i] << endl;
//    }
//}

// Case 1
template <typename T>
void print(T const& t) {
    cout << t << endl;
}

// Case 3
template<typename T1, typename... Args> // overloading
void print(T1 const& t, Args const& ... args) {
    cout << t << endl;
    print<Args...>(args...);
}

int main8787(int argc, const char * argv[]) {
    print(10.5, 42, std::string{"hello"}, "world");
    return 0;
}

template<int index, typename T, typename... Args>
struct retrieve_index {
    using type = typename retrieve_index<index-1, Args...>::type;
};

template<typename T, typename... Args> // specialization
struct retrieve_index<0, T, Args ...> {
    using type = T;
};

int main() {
    using rtype = retrieve_index<1, int, double*, float, std::string, char*>::type;
    cout << typeid(rtype).name() << endl;
    return 0;
}

