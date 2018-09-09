#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int charToNumber(char x) {
	switch (x) {
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}
	return 0;
}

int combineNumbers(char x, char y) {
	int numTensPlace = charToNumber(x)*10;
	int numOnesPlace = charToNumber(y);
	return (numTensPlace + numOnesPlace);
}

char intToChar(int x) {
	switch (x) {
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
}

int main() {
	string time;
	cin >> time;
	string newTime("00:00:00");

	if (time[8] == 'P') {
		int totalTime = combineNumbers(time[0], time[1]);

		if (totalTime < 12) {
			totalTime += 12;
		}

		if (totalTime >= 20) {
			newTime[0] = '2';
			totalTime -= 20;
			newTime[1] = intToChar(totalTime);
		}
		else if (totalTime >= 10) {
			newTime[0] = '1';
			totalTime -= 10;
			newTime[1] = intToChar(totalTime);
		}
		else {
			newTime[0] = '0';
			newTime[1] = intToChar(totalTime);
		}

		int i = 2;
		while (i != 8) {
			newTime[i] = time[i];
			++i;
		}

		cout << newTime << '\n';
	}
	else if (time[8] == 'A') {
		int i = 0;
		while (i != 8) {
			newTime[i] = time[i];
			++i;
		}
		if (time[0] == '1') {
			newTime[0] = '0';
			newTime[1] = '0';
		}
		cout << newTime << '\n';
	}

	return 0;
}
