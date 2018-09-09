#include <iostream>
#include <vector>

void merge(std::vector<int>* arr, int first, int mid, int last) {
	int n1 = mid - first + 1;
	int n2 = last - mid;

	std::vector<int> left(n1+1);
	std::vector<int> right(n2+1);

	for (int i = 0; i < n1; ++i) {
		left[i] = arr -> operator[](first + i);
	}
	for (int j = 0; j < n2; ++j) {
		right[j] = arr -> operator[](mid + 1 + j);
	}

	left[n1] = INT32_MAX;
	right[n2] = INT32_MAX;

	int i = 0;
	int j = 0;
	for (int k = first; k <= last; ++k) {
		if (left[i] <= right[j]) {
			arr -> operator[](k) = left[i];
			++i;
		}
		else {
			arr -> operator[](k) = right[j];
			++j;
		}
	}

}

void mergeSort(std::vector<int>* arr, int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(arr, first, mid);
		mergeSort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
}

int main() {
	int arraySize;
	std::cin >> arraySize;

	std::vector<int> someArray(arraySize);
	for (int i = 0; i < arraySize; ++i) {
		std::cin >> someArray[i];
	}
	
	std::cout << '\n';

	mergeSort(&someArray, 0, arraySize - 1);

	for (int i = 0; i < arraySize; ++i) {
		std::cout << someArray[i] << ' ';
	}
}