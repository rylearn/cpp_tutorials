
#include <iostream>
#include <ctime>
using namespace std;

long productToN(long n) {
	if (n == 1) {
		return 1;
	}
	return n * productToN(n - 1);
}

long productToN2(long n) {
	long res = n;
	for (long i = 1; i < n; ++i) {
		res *= (n - i);
	}
	return res;
}

int main() {
	clock_t begin = clock();
	cout << productToN(20) << endl;
	clock_t end = clock();
	cout << end - begin << endl;

	begin = clock();
	cout << productToN2(20) << endl;
	end = clock();
	cout << end - begin << endl;

	return 0;
}
