
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */


	int numOfIntegersInArray = 0;
	int numOfRotations = 0;
	int numberOfIndexAcceses = 0;

	cout << "Enter number of integers in array\n";
	cin >> numOfIntegersInArray;
	cout << "Enter number of rotations on array\n";
	cin >> numOfRotations;
	cout << "Enter number of index accesses of array\n";
	cin >> numberOfIndexAcceses;

	cout << "Enter array of " << numOfIntegersInArray << " integers\n";

	int* newArray = new int[numOfIntegersInArray];
	int i = 0;

	while (i != numOfIntegersInArray) {
		cin >> newArray[i];
		++i;
	}

	i = 0;
	int someNumber = 0;
	while (i != numberOfIndexAcceses) {
		cin >> someNumber;
		int desiredValue = (someNumber - numOfRotations%numOfIntegersInArray) < 0 ? ((someNumber - numOfRotations%numOfIntegersInArray) + numOfIntegersInArray) : (someNumber - numOfRotations%numOfIntegersInArray);
		if (desiredValue < 0) {
			cout << newArray[0] << '\n';
		}
		else {
			cout << newArray[desiredValue] << '\n';
		}
		++i;
	}

	delete[] newArray;

	return 0;
}
