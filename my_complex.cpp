#include <iostream>
#include <cmath>
#include <complex> // for comparison

namespace my_implementation {
	template<typename Scalar>
	class complex {
		Scalar re, im;
		Scalar base, exp;

	public:
		
		complex(const Scalar& r, const Scalar& i) :re{r}, im{i} {
			updatePolar();
		}

		complex(Scalar r) :re{r}, im{0} {
			updatePolar();
		}

		complex() :re{0}, im{0} {
			updatePolar();
		}

		Scalar real() const { 
			return re;
		}

		void real(Scalar d) {
			re = d;
		}

		Scalar imag() const {
			return im;
		}

		void imag(Scalar d) {
			im = d;
		}

		complex<Scalar>& operator+=(complex<Scalar> z) {
			re += z.re;
			im += z. im;
			return *this;
		}

		complex<Scalar>& operator-=(complex<Scalar> z) {
			re -= z.re;
			im -= z.im;
			return *this;
		}

		complex<Scalar>& operator*=(complex<Scalar> z) {
			Scalar old_re = re;
			Scalar old_im = im;
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

		complex<Scalar>& operator/=(complex<Scalar> z) {
			Scalar old_base = base;
			Scalar old_exp = exp;
			base = old_base / z.base;
			exp = old_exp - z.exp;
			updateRect();
			return *this;
		}

	};

	template<typename LeftType, typename RightType>
	complex<RightType> operator*(complex<LeftType> a, complex<RightType> b) {
		return a *= b;
	}

	template<typename LeftType, typename RightType>
	complex<RightType> operator/(complex<LeftType> a, complex<RightType> b) {
		return a /= b;
	}

	template<typename LeftType, typename RightType>
	complex<RightType> operator+(complex<LeftType> a, complex<RightType> b) {
		return a += b;
	}

	template<typename LeftType, typename RightType>
	complex<RightType> operator-(complex<LeftType> a, complex<RightType> b) {
		return a -= b;
	}

	template<typename Scalar>
	complex<Scalar> operator-(complex<Scalar> a) {
		return {-a.real(), -a.imag()};
	}

	template<typename Scalar>
	std::ostream& operator<<(std::ostream& os, const complex<Scalar>& comp) {
		return os << "(" << comp.real() << "," << comp.imag() << ")";
	}
}

int main() {
	my_implementation::complex<double> a {2, 1};
	my_implementation::complex<double> b {my_implementation::complex<double>{1} / a}; // to do: remove explicit construction
	my_implementation::complex<double> c {a+b*my_implementation::complex<double>{1, 2.3}};

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

