
#include <iostream>
using namespace std;

void swap(int& first, int& second) {
	int temp = first;
	first = second;
	second = temp;
}

int partition(int givenArray[], int start, int end) {
	int endValue = givenArray[end];\
	int index = start - 1;

	for (int j = start; j <= (end - 1); ++j) {
		if (givenArray[j] < endValue) {
			index++;
			swap(givenArray[index], givenArray[j]);
		}
	}
	swap(givenArray[index + 1], givenArray[end]);

	return (index + 1);
}

int* quicksort(int unsortedArray[], int start, int end) {
	if (start < end) {
		int pivot = partition(unsortedArray, start, end);
		quicksort(unsortedArray, start, pivot-1);
		quicksort(unsortedArray, pivot + 1, end);
	}

	return unsortedArray;
}

int* sortNumbers(int unsortedArray[], int totalArrayPossibilities) {
	return quicksort(unsortedArray, 0, totalArrayPossibilities - 1);
}

int main() {
	int sizeOfArray = 0;

	cout << "Enter your array size: ";
	cin >> sizeOfArray;
	int* array = new int[sizeOfArray];

	cout << "Enter the numbers: ";

	int i = 0;
	while (i != sizeOfArray) {
		cin >> array[i];
		++i;
	}

	swap(array[0], array[1]);
	sortNumbers(array, sizeOfArray);

	i = 0;
	while (i != sizeOfArray) {
		cout << array[i] << " ";
		++i;
	}

	return 0;
}
