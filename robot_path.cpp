
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

class Point {
public:
	int x;
	int y;
	Point(int new_x, int new_y) :x(new_x), y(new_y) {}
	friend ostream& operator<<(ostream&, const Point&);
};

ostream& operator<<(ostream& os, const Point& p) {
	os << p.x << " " << p.y;
	return os;
}

struct Nocase_hash {
	int d = 1;
	size_t operator()(const Point& p) const 
	{
		size_t h = 0;
		std::size_t h1 = std::hash<int>{}(p.x);
		std::size_t h2 = std::hash<int>{}(p.y);
		return h1 ^ (h2 << 1);
	}
};

struct Nocase_equal {
	bool operator()(const Point &p1, const Point &p2) const {
		return p1.x == p2.x && p1.y == p2.y;
	}
};

class Paths {
	int max_x;
	int max_y;

public:
	vector<Point> paths;
	unordered_map<int, vector<Point>> cache;
	int count;

	Paths(int max_x, int max_y) {
		this->max_x = max_x;
		this->max_y = max_y;
	}

	bool isOffLimits(int x, int y) {
		return x > max_x || y > max_y || x < 0 || y < 0;
	}

	int countPath(int x, int y) {
		if (x < 0 || y < 0 || isOffLimits(x, y)) {
			return false;
		}
		if (x == 0 && y == 0) {
			count += 1;
		}
		// paths.push_back(Point(x, y)); // binary tree to save the paths
		countPath(x, y - 1);
		countPath(x - 1, y);
		return count;
	}
	
};

int main () {
	int n = 4;
	Paths paths = Paths(n, n);
	cout << paths.countPath(n, n) << endl;
	return 0;
}
