//
//  main.cpp
//  functors
//
//  Created by qldo18 on 5/5/16.
//  Copyright (c) 2016 Qildo Inc. All rights reserved.
//

#include <iostream>
#include <cmath>

template <typename Q, typename Op>
Q apply_unary_op(Q const& x, Op op = Op{})
{
    return op(x);
}

template<typename T = void>   // primary template
struct squareRoot
{
    constexpr T operator()(const T &lhs) const
    {
        return std::sqrt(lhs);
    }
};

/*
struct squareRoot<>
{
    template<typename T>
    constexpr auto operator()( T&& lhs) const
    -> decltype(std::sqrt(std::forward<T>(lhs))){
        return std::sqrt(lhs);
    }
};*/

int main(int argc, const char * argv[]) {
    std::plus<double> z{};
    double x = 5;
    double r = apply_unary_op(x, squareRoot<>{});
    std::cout << r << std::endl;
    return 0;
}
