
#include <iostream>
#include <type_traits>
//typedef unsigned int uint32_t;
using namespace std;

template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    Pair(const T1& f, const T2& s) : first(f), second(s) {}
};

template <uint32_t N, typename T1, typename T2>
struct Getter {
    enum { count = N };
    using Type = typename Getter<1, T1, T2>::Type;
    Getter<N-1, T1, T2> getTemp;

    const Type& get(const Pair<T1, T2>& arg) {
        return getTemp.get(arg);
    }
};

template <uint32_t N, typename T1, typename T2, typename T3>
struct Getter<N, Pair<T1, T2>, T3> {
    static Getter<N, T1, T2> getterLeft;
    enum { count = getterLeft.count - 1 };
    
    Getter<count, T2, T3 > getterT3;
    
    using Type = typename decltype(getterT3)::Type;
    
    const Type& get(const Pair<Pair<T1, T2>, T3>& arg) {
        const Pair<T2, T3> newPair {arg.first.second, arg.second};
        
        cout << "Testing: count is " << count << endl;
        //return arg.second;
        
        const Type newType = getterT3.get(newPair);
        return newType;
    }
};

template <typename T1, typename T2>
struct Getter<0, T1, T2> {
    using Type = T1;
    uint32_t value_type = 0;
    const Type& get(const Pair<T1, T2>& arg) {
        return arg.first;
    }
};

template <typename T1, typename T2, typename T3>
struct Getter<0, Pair<T1, T2>, T3> {
    
    Getter<0, T1, T2> getterLeft;
    using Type = typename Getter<0, T1, T2>::Type;
    
    const Type& get(const Pair<Pair<T1, T2>, T3>& arg) {
        
        return getterLeft.get(arg.first);
    }
};

/*
 template <typename T1, typename T2, typename T3>
 struct Getter<0, T1, Pair<T2, T3> > {
 using Type = T1;
 const Type& get(const Pair<T1, Pair<T2, T3>>& arg) {
 Getter<0, T2, T3> getterRight;
 return getterRight.get(arg.second);
 }
 };*/

template <typename T1, typename T2>
struct Getter<1, T1, T2> {
    using Type = T2;
    uint32_t value_type = 1;
    const Type& get(const Pair<T1, T2>& arg) {
        return arg.second;
    }
};

template <typename T1, typename T2, typename T3>
struct Getter<1, Pair<T1, T2>, T3 > {
    
    Getter<1, T1, T2> getterRight;
    using Type = typename Getter<1, T1, T2>::Type;
    
    const Type& get(const Pair<Pair<T1, T2>, T3>& arg) {
        
        return getterRight.get(arg.first);
    }
};

/*
 template <typename T1, typename T2, typename T3>
 struct Getter<1, T1, Pair<T2, T3> > {
 using Type = T2;
 const Type& get(const Pair<T1, Pair<T2, T3>>& arg) {
 Getter<0, T2, T3> getterRight;
 return getterRight.get(arg.second);
 }
 };
 */

template <uint32_t idx, typename T1, typename T2>
typename Getter<idx, T1, T2>::Type
get(const Pair<T1, T2>& p){
    Getter<idx, T1, T2> getter;
    return getter.get(p);
}

int main(int argc, const char * argv[]) {
    Pair<int, double> p1(42, 3.14);
    
    std::cout << get<0>(p1) << std::endl;
    std::cout << get<1>(p1) << std::endl;
    
    Pair<Pair<int, double>, const char*> p2(p1, "hello");
    std::cout << get<0>(p2) << std::endl;
    std::cout << get<1>(p2) << std::endl; // 3.14
    std::cout << get<2>(p2) << std::endl;
    
    std::cout << "hello world" << std::endl;
    
    Pair<Pair<Pair<int, double>, const char*>, int> p3(p2, 9);
    std::cout << get<0>(p3) << std::endl;
    std::cout << get<1>(p3) << std::endl; // 3.14
    std::cout << get<2>(p3) << std::endl;
    std::cout << get<3>(p3) << std::endl;
    
    return 0;
}
