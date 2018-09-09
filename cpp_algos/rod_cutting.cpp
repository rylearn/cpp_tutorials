#include <iostream>

int max(int one, int two);
int cutRod(int* prices, int n);

int max(int one, int two) {
	return one > two ? one : two;
}

int cutRod(int* prices, int n) {
	if (n == 0) {
		return 0;
	}
	int q = INT32_MIN;
	for (int i = 1; i <= n; ++i) {
		q = max(q, prices[i] + cutRod(prices, (n - i)));
	}
	return q;
}

int memoizedCutRodAux(int* prices, int n, int* newArray) {
	if (newArray[n] >= 0) {
		return newArray[n];
	}
	int q;
	if (n == 0) {
		q = 0;
	}
	else {
		q = INT32_MIN;
		for (int i = 1; i <= n; ++i) {
			q = max(q, prices[i] + memoizedCutRodAux(prices, n - i, newArray));
		}
		newArray[n] = q;
	}
	return q;
}

int memoizedCutRod(int* prices, int n) {
	int* newArray = new int[(n+1)];
	for (int i = 0; i <= n; ++i) {
		newArray[i] = INT32_MIN;
	}
	return memoizedCutRodAux(prices, n, newArray);
}

int bottomUpCutRod(int* prices, int n) {
	int* newArray = new int[(n + 1)];
	newArray[0] = 0;
	for (int j = 1; j <= n; ++j) {
		int q = INT32_MIN;
		for (int i = 1; i <= j; ++i) {
			q = max(q, prices[i] + newArray[(j - i)]);
		}
		newArray[j] = q;
	}
	return newArray[n];
}



int main() {
	int length;
	std::cin >> length;
	length++;
	int* prices = new int[length];
	prices[0] = 0;

	for (int i = 1; i < length; ++i) {
		std::cin >> prices[i];
	}

	std::cout << bottomUpCutRod(prices, 0) << std::endl;
	std::cout << bottomUpCutRod(prices, 1) << std::endl;
	std::cout << bottomUpCutRod(prices, 2) << std::endl;
	std::cout << bottomUpCutRod(prices, 3) << std::endl;
	std::cout << bottomUpCutRod(prices, 4) << std::endl;
	std::cout << bottomUpCutRod(prices, 5) << std::endl;

	return 0;
}
