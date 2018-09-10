#include <iostream>
#include <cstdint>
#include <string>

using std::cout;
using std::endl;

using std::declval;

struct TRUE {
    static constexpr bool value = true;
};

struct FALSE {
    static constexpr bool value = false;
};

template <typename T>
constexpr auto eval(T) -> decltype(T::value) { return T::value; }

template <typename T>
constexpr auto eval(void) -> decltype(T::value) { return T::value; }

template <bool p> struct foo {
    static std::string msg(void) { return "true"; }
};

template <> struct foo<false> {
    static std::string msg(void) { return "false"; }
};

template <typename T, typename test=decltype(declval<T>()[0])>
TRUE has_op_bracket(void) { return TRUE{}; }


template <typename T, typename... not_used>
FALSE has_op_bracket(not_used...) { return FALSE{}; }

template <typename T>
using HasBracket = decltype(has_op_bracket<T>());

template <typename T>
void check_bracket(void) {
    cout << std::boolalpha;
    cout << eval<HasBracket<T>>() << endl;
}

struct Hack {
    void foo(int) {}
};

template <typename T, typename test = decltype(declval<T>().foo(0))>
TRUE has_foo(void) { return TRUE{}; }

template <typename T, typename... not_used>
FALSE has_foo(not_used...) { return FALSE{}; }

int main4343(void) {
    //has_op_bracket<int>();
    //check_bracket<int>();
    //check_bracket<int*>();
    //check_bracket<std::string>();
    
    cout << std::boolalpha;
    cout << has_foo<Hack>().value << endl;
    return 0;
}

template <typename... T>
struct Tuple;

template <typename T>
struct Tuple<T> {
    T val;
};

template <typename T, typename... OtherArgs>
struct Tuple<T, OtherArgs...> : public Tuple<OtherArgs...> {
    T val;
};


int main343434(void) {
    Tuple<int> x;
    x.val = 42;
    
    cout << x.val << endl;
    
    Tuple<int, std::string> y;
    y.val = 0;
    
    Tuple<std::string>& y_tail = y;
    y_tail.val = "Hello World";
    
    cout << y_tail.val << endl;
    
    Tuple<int, double, std::string> z;
    z.val = 4;
    Tuple<std::string>& z_last = z;
    //Tuple<double>& z_mid = z;
    z_last.val = "ered";
    
    cout << z.val << endl;
    return 0;
}

template <int index, typename T>
struct loop {
    static constexpr int value = index * loop<index - 1, T>::value;
};

template <typename T> struct loop<0, T> {
    static constexpr int value = 1;
};

int x[loop<6, int>::value];

int main7678789() {
    cout << loop<6, int>::value << endl;
    return 0;
}

template <typename T> struct tail_tuple;

template <typename T, typename... Tail> struct tail_tuple<Tuple<T, Tail...>> {
    using type = Tuple<Tail...>;
};

template <int index, typename T>
struct tuple_loop {
    using short_tuple = typename tail_tuple<T>::type;
    using type = typename tuple_loop < index - 1, short_tuple>::type;
    
    static type& extract(T& arg) {
        return tuple_loop<index - 1, short_tuple>::extract(arg);
    }
};

template <typename T>
struct tuple_loop<0, T> {
    using type = decltype(declval<T>().val);
    static type& extract(T& arg) { return arg.val; }
};


int main(void) {
    using T = Tuple<int, std::string, double>;
    using test = tuple_loop<0, T>::type;
    
    T x;
    
    tuple_loop<0, T>::extract(x) = 14.8;
    tuple_loop<1, T>::extract(x) = "hello world";
    tuple_loop<0, T>::extract(x) = 19.8;
    tuple_loop<2, T>::extract(x) = 16.9;
    
    cout << tuple_loop<0, T>::extract(x) << endl;
    cout << tuple_loop<1, T>::extract(x) << endl;
    cout << tuple_loop<2, T>::extract(x) << endl;
    return 0;
}
