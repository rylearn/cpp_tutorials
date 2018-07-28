
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int magic_index(vector<int>& x) 
{
	for (int i = 0; i < x.size(); ++i) {
		if (x[i] == i) {
			return i;
		}
	}
	return -1;
}

int magic_index_fast(vector<int>& x) 
{
	if (x.size() == 0) {
		return -1;
	}
	int mid = x.size() / 2;
	if (x[mid] == mid) {
		return x[mid];
	}
	else if (x[mid] > mid) {
		vector<int> y;
		copy(x.begin(), x.begin() + mid, back_inserter(y));
		return magic_index_fast(y);
	}
	int sz = x.end() - (x.begin() + mid + 1);
	vector<int> y(sz);
	
	copy(x.begin() + mid + 1, x.end(), y.begin());
	return magic_index_fast(y);
}

int main() {
	vector<int> x = {1, 1, 4, 5, 6};
	cout << magic_index(x) << endl;
	cout << magic_index_fast(x) << endl;
	return 0;
}
