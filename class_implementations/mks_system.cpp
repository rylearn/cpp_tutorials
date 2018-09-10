//
//  main.cpp
//  april282016p2
//
//  Created by qldo18 on 5/14/16.
//  Copyright (c) 2016 Qildo Inc. All rights reserved.
//

#include <iostream>

template <typename T, int ME, int SE, int GE, int NUM, int DEN>
class MKS {
    T value;
public:
    typedef MKS<T, ME, SE, GE, NUM, DEN> Same;
    static char unit_name[8];
    
    explicit MKS(double x = 0.0) : value(x) {}
    MKS(const Same& that) : value(that.value) {}
    
    ~MKS(void) {}
    
    T getValue(void) const { return value; }
    
    Same& operator=(const Same& that) {
        value = that.value;
        return *this;
    }
    
    Same operator+(const Same& that) const {
        return Same(value + that.value);
    }
    
    Same operator-(const Same& that) const {
        return Same(value - that.value);
    }
    
    Same operator+=(const Same& that) const {
        return value += that.value;
    }
    
    Same operator-=(const Same& that) const {
        return value -= that.value;
    }
    
    Same operator-(void) const { return Same(-value); }
    
    bool operator==(const Same& that) const {
        return value == that.value;
    }
    bool operator<(const Same& that) const {
        return value < that.value;
    }
    bool operator>(const Same& that) const {
        return that < *this;
    }
    bool operator<=(const Same& that) const {
        return value <= that.value;
    }
    bool operator>=(const Same& that) const {
        return value >= that.value;
    }
    bool operator!=(const Same& that) const {
        return value != that.value;
    }
    
    Same operator*(double scale) const {
        return Same(scale * value);
    }
    
    Same operator/(double scale) const {
        return Same(value / scale);
    }
    
    template <int ME2, int SE2, int GE2, int NUM2, int DEN2>
    MKS<T, ME+ME2, SE+SE2, GE+GE2, NUM, DEN>
    operator*(const MKS<T, ME2, SE2, GE2, NUM2, DEN>& that) const {
        return MKS<T, ME+ME2, SE+SE2, GE+GE2, NUM, DEN>(value * NUM2 * that.getValue() / DEN2);
    }
    
    template <int ME2, int SE2, int GE2, int NUM2, int DEN2>
    MKS<T, ME-ME2, SE-SE2, GE-GE2, NUM, DEN>
    operator/(const MKS<T, ME2, SE2, GE2, NUM2, DEN2>& that) const {
        return MKS<T, ME-ME2, SE-SE2, GE-GE2, NUM, DEN>((value*DEN2)/(that.getValue() * NUM2));
    }
    
    template <int NUM2, int DEN2>
    operator MKS<T, ME, SE, GE, NUM2, DEN2>(void) const {
        double convertMeTo1 = (double) NUM / (double) DEN;
        double convert1toThem = (double) DEN2 / (double) NUM2;
        return MKS<T, ME, SE, GE, NUM2, DEN2>(T{value*convertMeTo1*convert1toThem });
    }
};

template <typename T, int ME, int SE, int GE, int NUM, int DEN>
MKS<T, ME, SE, GE, NUM, DEN> operator*(T x, const MKS<T, ME, SE, GE, NUM, DEN>& y) {
    return MKS<T, ME, SE, GE, NUM, DEN> (x * y.getValue());
}

template <typename T, int ME, int SE, int GE, int NUM, int DEN>
MKS<T, -ME, -SE, -GE, NUM, DEN> operator/(T x, const MKS<T, ME, SE, GE, NUM, DEN>& y) {
    return MKS<T, -ME, -SE, -GE, NUM, DEN>(x / y.getValue());
}

template<typename T, int ME, int SE, int GE, int NUM, int DEN>
std::ostream& operator<<(std::ostream& ost, const MKS<T, ME, SE, GE, NUM, DEN>& x) {
    return ost << x.getValue() << MKS<T, ME, SE, GE, NUM, DEN>::unit_name;
}

template <typename T, int ME, int SE, int GE, int NUM, int DEN>
char MKS<T, ME, SE, GE, NUM, DEN>::unit_name[] = "MKS";

template <typename T> using Meter = MKS<T, 1, 0, 0, 1, 1>;
template <> char MKS<double, 1, 0, 0, 1, 1>::unit_name[] = "m";

template <typename T> using Kilometer = MKS<T, 1, 0, 0, 1000, 1>;
template <> char MKS<double, 1, 0, 0, 1000, 1>::unit_name[] = "km";

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
