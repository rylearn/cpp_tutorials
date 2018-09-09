
#include <vector>
#include <iostream>

int mergeResults(int* x, int first, int mid, int last, int firstLarge, int secondLarge) {
	int count = 0;
	for (int i = first; i <= last; ++i) {
		if (x[i] == firstLarge) {
			++count;
		}
	}
	if (count > ((last-first+1)/2) ) {
		return firstLarge;
	} 
	
	count = 0;
	for (int i = first; i <= last; ++i) {
		if (x[i] == secondLarge) {
			++count;
		}
	}
	if (count > ((last-first+1)/2) ) {
		return secondLarge;
	}

	return 0;
}

int findMajorityElement(int* x, int size, int first, int last) {
	if (size == 0) {
		return 0;
	}
	if (size == 1) {
		return x[0];
	}
	int mid = (first+last)/2;
	int firstLarge = findMajorityElement(x, (mid-first)+1, first, mid);
	int secondLarge = findMajorityElement(x, (last-(mid+1))+1, mid+1, last);

	return mergeResults(x, first, mid, last, firstLarge, secondLarge);
}

int main() {
	int numIntegers;
	std::cin >> numIntegers;
	int* someNumbers = new int[numIntegers];

	int i = 0;
	while (i != numIntegers) {
		std::cin >> someNumbers[i];
		++i;
	}

	int result = findMajorityElement(someNumbers, numIntegers, 0, numIntegers - 1);
	std::cout << result << std::endl;
	return 0;
}
