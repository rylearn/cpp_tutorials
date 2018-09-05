// Valarray.h

#ifndef _Valarray_h
#define _Valarray_h

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include "Vector.h"

using std::cout;
using std::endl;
using std::complex;

template <typename>
struct SRank;

template <> struct SRank<int> {
    static constexpr int value = 1;
    static constexpr bool is_complex = false;
};
template <> struct SRank<float> {
    static constexpr int value = 2;
    static constexpr bool is_complex = false;
};
template <> struct SRank<double> {
    static constexpr int value = 3;
    static constexpr bool is_complex = false;
};
template <typename T> struct SRank<complex<T>> {
    static constexpr int value = SRank<T>::value;
    static constexpr bool is_complex = true;
};

template <int, int>
struct SType;

template <> struct SType<1, 0> { using type = int; };
template <> struct SType<2, 0> { using type = float; };
template <> struct SType<3, 0> { using type = double; };
template <> struct SType<1, 1> { using type = complex<int>; };
template <> struct SType<2, 1> { using type = complex<float>; };
template <> struct SType<3, 1> { using type = complex<double>; };

template <typename T1, typename T2>
struct choose_type {
    
    static constexpr int t1_rank = SRank<T1>::value;
    static constexpr int t2_rank = SRank<T2>::value;
    
    static constexpr bool t1_complex = SRank<T1>::is_complex;
    static constexpr bool t2_complex = SRank<T2>::is_complex;
    
    //	static constexpr int max_rank = (t1_rank > t2_rank) ? t1_rank : t2_rank;
    static constexpr int max_rank = (t1_rank < t2_rank) ? t2_rank : t1_rank;
    static constexpr int complex_rank = (t1_complex || t2_complex) ? 1 : 0;
    
    using type = typename SType<max_rank, complex_rank>::type;
};

template <typename T1, typename T2>
using ChooseType = typename choose_type<T1, T2>::type;

template <typename T1, typename T2, typename Op>
ChooseType<T1, T2> apply_indiv_op(T1 x, T2 y, Op op = Op{})
{
    ChooseType<T1, T2> x1 = (ChooseType<T1, T2>)x;
    ChooseType<T1, T2> x2 = (ChooseType<T1, T2>)y;
    return op(x1, x2);
}


template< class T >
class squareRoot;

template< class T = void >
class squareRoot;

template<>
class squareRoot<void>;

template<>
class squareRoot<void>
{
public:
    template< class T>
    constexpr auto operator()(T&& lhs) const
    -> decltype(std::sqrt(std::forward<T>(lhs))) {
        return std::sqrt(std::forward<T>(lhs));
    }
};

template <typename T, typename Op>
T apply_unary_op(T const& x, Op op = Op{})
{
    return op(x);
}

/*
 template< class T > struct sum;
 template<class T = void> struct sum;
 constexpr T operator()(const T &lhs, const T &rhs) const
 {
	return lhs + rhs;
 }
 */

template <typename S1Type, typename S2Type, typename Operation>
class ProxValarray;

template <typename S1Type, typename Operation>
class ProxUnaryValarray;

template <typename X>
class ConstWrapper;

template <typename S>
struct Wrap : public S {
    using S::S;
    Wrap() : S() {}
    Wrap(const S& arg) : S(arg) {}
    
    template <typename T>
    Wrap<S>(const Wrap<T>& arg) : S(arg.size())
    {
        uint64_t sizeTemp = arg.size();
        for (uint64_t k = 0; k < sizeTemp; ++k)
        {
            this->operator[](k) = arg[k];
        }
    }
    
    Wrap(const Wrap& arg) :S(arg) {
    }
    
    Wrap<S>& operator=(const Wrap<S>& arg) {
        uint64_t sizeTemp = std::min(this->size(), arg.size());
        for (int k = 0; k < sizeTemp; ++k) {
            this->operator[](k) = arg[k];
        }
        return *this;
    }
    
    template <typename T>
    Wrap<S>& operator=(const Wrap<T>& arg) {
        uint64_t sizeTemp = std::min(this->size(), arg.size());
        for (int k = 0; k < sizeTemp; ++k) {
            this->operator[](k) = arg[k];
        }
        return *this;
    }
    
    template <typename T>
    Wrap<ProxValarray<S, T, std::plus<>>> operator+(const Wrap<T>& rhs)
    {
        S const& left{ *this };
        T const& right{ rhs };
        ProxValarray<S, T, std::plus<>> result{ left, right, std::plus<>{} };
        Wrap<ProxValarray<S, T, std::plus<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    template <typename T>
    Wrap<ProxValarray<S, T, std::minus<>>> operator-(const Wrap<T>& rhs)
    {
        S const& left{ *this };
        T const& right{ rhs };
        ProxValarray<S, T, std::minus<>> result{ left, right, std::minus<>{} };
        Wrap<ProxValarray<S, T, std::minus<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    Wrap<ProxUnaryValarray<S, std::negate<>>> operator-(void)
    {
        S const& right{ *this };
        ProxUnaryValarray<S, std::negate<>> result{ right, std::negate<>{} };
        Wrap<ProxUnaryValarray<S, std::negate<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    template <typename T>
    Wrap<ProxValarray<S, T, std::multiplies<>>> operator*(const Wrap<T>& rhs)
    {
        S const& left{ *this };
        T const& right{ rhs };
        ProxValarray<S, T, std::multiplies<>> result{ left, right, std::multiplies<>{} };
        Wrap<ProxValarray<S, T, std::multiplies<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    template <typename T>
    Wrap<ProxValarray<S, T, std::divides<>>> operator/(const Wrap<T>& rhs)
    {
        S const& left{ *this };
        T const& right{ rhs };
        ProxValarray<S, T, std::divides<>> result{ left, right, std::divides<>{} };
        Wrap<ProxValarray<S, T, std::divides<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    Wrap<ProxUnaryValarray<S, squareRoot<>>> sqrt(void)
    {
        S const& left{ *this };
        ProxUnaryValarray<S, squareRoot<>> result{ left, squareRoot<>{} };
        Wrap<ProxUnaryValarray<S, squareRoot<>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    typedef typename S::value_type value_type;
    
    value_type accumulate(std::function<value_type(value_type, value_type)> func)
    {
        S const& givenObject{ *this };
        
        value_type returnVal = 0;
        
        if (this->size() == 1) {
            return givenObject[0];
        }
        else if (this->size() > 1) {
            returnVal = func(givenObject[0], givenObject[1]);
            for (uint64_t k = 2; k < this->size(); k++) {
                
                returnVal = func(returnVal, givenObject[k]);
            }
        }
        return returnVal;
    }
    
    Wrap<ProxUnaryValarray<S, std::function<value_type(value_type)>>> apply(std::function<value_type(value_type)> func)
    {
        S const& left{ *this };
        ProxUnaryValarray<S, std::function<value_type(value_type)>> result{ left, func };
        Wrap<ProxUnaryValarray<S, std::function<value_type(value_type)>>> wrapped_result{ result };
        return wrapped_result;
    }
    
    value_type sum(void)
    {
        value_type returnVal{ 0 };
        for (uint64_t k = 0; k < this->size(); ++k) {
            returnVal = returnVal + this->operator[](k);
        }
        return returnVal;
    }
};

template <typename T>
using valarray = Wrap<epl::vector<T>>;

template <typename Op, typename T>
void apply_op(valarray<T>& lhs, valarray<T> const& x, valarray<T> const &y, Op op = Op{})
{
    uint64_t size = std::min(x.size(), y.size());
    size = (size < lhs.size()) ? size : lhs.size();
    for (uint64_t k = 0; k < size; k += 1) {
        lhs[k] = op(x[k], y[k]);
    }
}

template <typename T> struct choose_ref2 {
    using type = T;
};
template <typename T> struct choose_ref2<epl::vector<T>> {
    using type = const epl::vector<T>&;
};
template <typename T> using ChooseRef2 = typename choose_ref2<T>::type;


template <typename S1Type, typename S2Type, typename Operation>
class ProxValarray {
public:
    using ltype = typename S1Type::value_type;
    using rtype = typename S2Type::value_type;
    using value_type = ChooseType<ltype, rtype>;
    
    using LeftType = ChooseRef2<S1Type>;
    using RightType = ChooseRef2<S2Type>;
    
    LeftType s1;
    RightType s2;
    
    Operation op;
    
    ProxValarray(LeftType const& left, RightType const& right, Operation const& operation) :
    s1(left), s2(right), op(operation) {}
    
    uint64_t size(void) const { return std::min(s1.size(), s2.size()); }
    
    ChooseType<ltype, rtype> operator[](uint64_t k) const {
        uint64_t size = std::min(s1.size(), s2.size());
        if (k < size) {
            ChooseType<ltype, rtype> result;
            result = apply_indiv_op(s1[k], s2[k], op);
            return result;
        }
        else {
            if (s1.size() > k) {
                return (value_type)s1[k]; // SJ: check
            }
            else if (s2.size() > k) {
                return (value_type)s2[k];
            }
        }
    }
    
    void print(std::ostream& out) const {
        const char* pref = "";
        uint64_t k = 0;
        ChooseType<ltype, rtype> result;
        while (k < s1.size() && k < s2.size()) {
            result = apply_indiv_op(s1[k], s2[k], op);
            out << pref << result;
            pref = ", ";
            k++;
        }
        while (s1.size() > k) {
            out << pref << (ChooseType<ltype, rtype>)s1[k];
            pref = ", ";
            k++;
        }
        while (s2.size() > k) {
            out << pref << (ChooseType<ltype, rtype>)s2[k];
            pref = ", ";
            k++;
        }
    }
};

template <typename S1Type, typename Operation>
class ProxUnaryValarray {
public:
    using ltype = typename S1Type::value_type;
    using value_type = ltype;
    using LeftType = ChooseRef2<S1Type>;
    LeftType s1;
    Operation op;
    
    ProxUnaryValarray(LeftType const& left, Operation const& operation) :
    s1(left), op(operation) {}
    
    uint64_t size(void) const { return s1.size(); }
    
    ltype operator[](uint64_t k) const {
        uint64_t size = s1.size();
        if (k < size) {
            ltype result;
            result = apply_unary_op(s1[k], op);
            return result;
        }
        else {
            return 0;
        }
    }
    
    void print(std::ostream& out) const {
        const char* pref = "";
        uint64_t k = 0;
        ltype result;
        while (k < s1.size()) {
            result = apply_unary_op(s1[k], op);
            out << pref << result;
            pref = ", ";
            k++;
        }
    }
};

template <typename X>
class ConstWrapper {
    X value;
public:
    ConstWrapper(X val) { this->value = val; }
    X operator[](uint64_t k) const { return value; }
    uint64_t size(void) const { return 1000; }
    void print(std::ostream& out) const {
        out << value;
    }
    using value_type = X;
};

template <typename T1, typename T2>
Wrap<ProxValarray<ConstWrapper<T1>, T2, std::plus<>>> operator+(const T1& lhs, const Wrap<T2>& rhs)
{
    using ConstType = ConstWrapper<T1>;
    ConstType left{ lhs };
    T2 const& right{ rhs };
    ProxValarray<ConstType, T2, std::plus<>> result{ left, right, std::plus<>{} };
    Wrap<ProxValarray<ConstType, T2, std::plus<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<T1, ConstWrapper<T2>, std::plus<>>> operator+(const Wrap<T1>& lhs, const T2& rhs)
{
    using ConstType = ConstWrapper<T2>;
    T1 const& left{ lhs };
    ConstType right{ rhs };
    ProxValarray<T1, ConstType, std::plus<>> result{ left, right, std::plus<>{} };
    Wrap<ProxValarray<T1, ConstType, std::plus<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<ConstWrapper<T1>, T2, std::minus<>>> operator-(const T1& lhs, const Wrap<T2>& rhs)
{
    using ConstType = ConstWrapper<T1>;
    ConstType left{ lhs };
    T2 const& right{ rhs };
    ProxValarray<ConstType, T2, std::minus<>> result{ left, right, std::minus<>{} };
    Wrap<ProxValarray<ConstType, T2, std::minus<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<T1, ConstWrapper<T2>, std::minus<>>> operator-(const Wrap<T1>& lhs, const T2& rhs)
{
    using ConstType = ConstWrapper<T2>;
    T1 const& left{ lhs };
    ConstType right{ rhs };
    ProxValarray<T1, ConstType, std::minus<>> result{ left, right, std::minus<>{} };
    Wrap<ProxValarray<T1, ConstType, std::minus<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<ConstWrapper<T1>, T2, std::multiplies<>>> operator*(const T1& lhs, const Wrap<T2>& rhs)
{
    using ConstType = ConstWrapper<T1>;
    ConstType left{ lhs };
    T2 const& right{ rhs };
    ProxValarray<ConstType, T2, std::multiplies<>> result{ left, right, std::multiplies<>{} };
    Wrap<ProxValarray<ConstType, T2, std::multiplies<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<T1, ConstWrapper<T2>, std::multiplies<>>> operator*(const Wrap<T1>& lhs, const T2& rhs)
{
    using ConstType = ConstWrapper<T2>;
    T1 const& left{ lhs };
    ConstType right{ rhs };
    ProxValarray<T1, ConstType, std::multiplies<>> result{ left, right, std::multiplies<>{} };
    Wrap<ProxValarray<T1, ConstType, std::multiplies<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<ConstWrapper<T1>, T2, std::divides<>>> operator/(const T1& lhs, const Wrap<T2>& rhs)
{
    using ConstType = ConstWrapper<T1>;
    ConstType left{ lhs };
    T2 const& right{ rhs };
    ProxValarray<ConstType, T2, std::divides<>> result{ left, right, std::divides<>{} };
    Wrap<ProxValarray<ConstType, T2, std::divides<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T1, typename T2>
Wrap<ProxValarray<T1, ConstWrapper<T2>, std::divides<>>> operator/(const Wrap<T1>& lhs, const T2& rhs)
{
    using ConstType = ConstWrapper<T2>;
    T1 const& left{ lhs };
    ConstType right{ rhs };
    ProxValarray<T1, ConstType, std::divides<>> result{ left, right, std::divides<>{} };
    Wrap<ProxValarray<T1, ConstType, std::divides<>>> wrapped_result{ result };
    return wrapped_result;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Wrap<T>& vec) {
    const char* pref = "";
    for (uint64_t k = 0; k < vec.size(); ++k) {
        out << pref << vec[k];
        pref = ", ";
    }
    return out;
}

#endif /* _Valarray_h */

