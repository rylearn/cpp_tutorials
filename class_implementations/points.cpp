
#include <iostream>
#include <vector>
using namespace std;

struct Point {
	int x, y;

	Point() {}
};

struct Points {
	vector<Point> elem;
	Points(Point p0) {
		elem.push_back(p0);
	}
	Points(Point p0, Point p1) {
		elem.push_back(p0);
		elem.push_back(p1);
	}
};


int main () {
	Point p1 {};
	cout << p1.x << ' ' << p1.y << endl;
	return 0;
}