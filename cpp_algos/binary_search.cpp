
#include <iostream>
#include <vector>

int binarySearch(int someValue, std::vector<int> someArray, int start, int end) {
	if (start <= end) {
		int mid = (start + end) / 2;
		if (someArray[mid] == someValue) {
			return mid;
		}
		else if (someArray[mid] > someValue) {
			return binarySearch(someValue, someArray, start, mid - 1);
		}
		else if (someArray[mid] < someValue) {
			return binarySearch(someValue, someArray, mid + 1, end);
		}
	}
	return -1;
}

int main() {
	while (true) {
		int arraySize;
		std::cin >> arraySize;

		std::vector<int> sortedArray;
		for (int i = 0; i < arraySize; ++i) {
			int temp;
			std::cin >> temp;
			sortedArray.push_back(temp);
		}

		int numSearches;
		std::cin >> numSearches;
		std::vector<int> searchForThese;

		for (int j = 0; j < numSearches; ++j) {
			int temp;
			std::cin >> temp;
			searchForThese.push_back(temp);
		}

		for (int j = 0; j < numSearches; ++j) {
			std::cout << binarySearch(searchForThese[j], sortedArray, 0, sortedArray.size() - 1) << ' ';
		}

		std::cout << '\n';
	}
}
