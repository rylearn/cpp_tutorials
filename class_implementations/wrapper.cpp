#include <iostream>
#include <cstdint>

using std::cout;
using std::endl;

template<typename T>
struct Wrap : public T {
    using T::T;
    Wrap(T const& arg) : T(arg) {}
};

template <typename T>
void foo(T const&) {
    cout << "general\n";
}

template <typename T>
void foo(Wrap<T> const&) {
    cout << "specific to wrapped stuff\n";
}

void foo(int const&) {
    cout << "specific to int\n";
}

struct Blah{};

template <typename T>
Wrap<T> wrap(T const& x) {
    return Wrap<T> { x };
}

int main(void) {
    foo(42);
    Blah b;
    foo(b);
    foo(wrap(b));
    return 0;
}