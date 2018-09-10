
#include <iostream>
#include <complex>

template <bool Check, typename T1, typename T2>
struct conditional {
    using Type = T1;
};

template<typename T1, typename T2>
struct conditional<false, T1, T2> {
    using Type = T2;
};

template <typename T1, typename T2>
struct Bigger {
    using Type = typename conditional<(sizeof(T1)>sizeof(T2)), T1, T2>::Type;
};

template <typename T1, typename T2>
using BiggerType = typename Bigger<T1, T2>::Type;

struct FooBar {
    int q;
    int r;
    int o;
    int o2;
};

struct Foo {
    int q;
    int r;
    int o;
    double o2;
};

int main(int argc, const char * argv[]) {
    double x = 2;
    std::complex<double> y = 3;
    BiggerType<Foo, FooBar> q;
    std::cout << typeid(q).name() << std::endl;
    return 0;
}
