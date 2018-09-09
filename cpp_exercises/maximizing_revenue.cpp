#include <iostream>
#include <vector>
#include <string>
#include <math.h>

bool isGreaterOrEqual(int digit, int max_digit) {

	if (max_digit < 0 && digit > 0) {
		return true;
	}

	std::string firstString = std::to_string(digit);
	std::string secondString = std::to_string(max_digit);

	int i = 0;
	int j = 0;

	if (firstString.size() == secondString.size()) {
		return digit > max_digit;
	}

	std::string largerString;
	std::string smallerString;
	if (firstString.size() > secondString.size()) {
		largerString = firstString;
		smallerString = secondString;
	}
	else {
		largerString = secondString;
		smallerString = firstString;
	}

	while (i != smallerString.size()) {
		int firstDigit = (int)largerString[j] - '0';
		int secondDigit = (int)smallerString[i] - '0';

		if (firstDigit > secondDigit) {
			if (largerString == firstString) {
				return true;
			}
			else {
				return false;
			}	
		}
		else if (secondDigit > firstDigit) {
			if (largerString == secondString) {
				return true;
			}
			else {
				return false;
			}
		}

		++j;
		++i;
	}

	std::string first = std::to_string(digit);
	std::string second = std::to_string(max_digit);

	std::string firstConcat = first + second;
	std::string secondConcat = second + first;

	std::string::size_type sz;
	int first_dec = std::stoi(firstConcat, &sz);
	int second_dec = std::stoi(secondConcat, &sz);

	return (first_dec > second_dec);

}

std::string largestNumber(std::vector<int> digits) {
	std::string answer;
	std::vector<bool> checkBefore;
	checkBefore.resize(digits.size(), true);
	int i = 0;
	while (i != digits.size()) {
		int maxDigit = -INT32_MAX;
		int j = 0;
		int desiredIndex;
		bool desiredIndexSet = false;

		for (j = 0; j < digits.size(); ++j) {
			if (isGreaterOrEqual(digits[j], maxDigit) && checkBefore[j]) {
				if (desiredIndexSet) {
					checkBefore[desiredIndex] = true;
				}
				else {
					desiredIndexSet = true;
				}			
				desiredIndex = j;
				maxDigit = digits[j];
				checkBefore[desiredIndex] = false;
			}
		}
		answer.append(std::to_string(maxDigit));
		++i;
	}
	return answer;
}

int main() {
		int numIntegers;
		std::cin >> numIntegers;

		std::vector<int> integers(numIntegers);
		for (int i = 0; i < numIntegers; ++i) {
			std::cin >> integers[i];
		}

		std::cout << largestNumber(integers);
}
