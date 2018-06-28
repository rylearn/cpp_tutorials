
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class T>
T sum(vector<T>& v)
{
	T sum = 0;
	for (const T& x : v)
		sum += x;
	return sum;
}

template<class T>
void incr(vector<T>& v)
{
	for (T& x : v)
		x++;
}

int main() {
	vector<int> v = {7, 5, 16, 8};
	cout << sum(v) << endl;
	incr(v);
	cout << sum(v) << endl;
	return 0;
}
