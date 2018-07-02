#include <iostream>
#include <cmath>
#include <complex> // for comparison

namespace my_implementation {
	class complex {
		double re, im;
		double base, exp;

	public:
		
		complex(double r, double i) :re{r}, im{i} {
			updatePolar();
		}

		complex(double r) :re{r}, im{0} {
			updatePolar();
		}

		complex() :re{0}, im{0} {
			updatePolar();
		}

		double real() const { 
			return re;
		}

		void real(double d) {
			re = d;
		}

		double imag() const {
			return im;
		}

		void imag(double d) {
			im = d;
		}

		complex& operator+=(complex z) {
			re += z.re;
			im += z. im;
			return *this;
		}

		complex& operator-=(complex z) {
			re -= z.re;
			im -= z.im;
			return *this;
		}

		complex& operator*=(complex z) {
			double old_re = re;
			double old_im = im;
			re = old_re * z.re - old_im * z.im;
			im = old_re * z.im + old_im * z.re;
			updatePolar();
			return *this;
		}

		void updatePolar() {
			base = sqrt(pow(re, 2) + pow(im, 2));
			if (re != 0)
				exp = atan(im / re);
			else
				exp = 0;
		}

		void updateRect() {
			re = base * cos(exp);
			im = base * sin(exp);
		}

		complex& operator/=(complex z) {
			double old_base = base;
			double old_exp = exp;
			base = old_base / z.base;
			exp = old_exp - z.exp;
			updateRect();
			return *this;
		}

	};

	complex operator*(complex a, complex b) {
		return a *= b;
	}

	complex operator/(complex a, complex b) {
		return a /= b;
	}

	complex operator+(complex a, complex b) {
		return a += b;
	}

	complex operator-(complex a, complex b) {
		return a -= b;
	}

	complex operator-(complex a) {
		return {-a.real(), -a.imag()};
	}

	std::ostream& operator<<(std::ostream& os, const complex& comp) {
		return os << "(" << comp.real() << "," << comp.imag() << ")";
	}
}

int main() {
	my_implementation::complex a {2, 1};
	my_implementation::complex b {1/a};
	my_implementation::complex c {a+b*my_implementation::complex{1, 2.3}};
	
	std::cout << -a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;

	std::complex<double> a2 {2, 1};
	std::complex<double> b2 {1./a2};
	std::complex<double> c2 {a2+b2*std::complex<double>{1, 2.3}};

	std::cout << -a2 << std::endl;
	std::cout << b2 << std::endl;
	std::cout << c2 << std::endl;
	return 0;
}
