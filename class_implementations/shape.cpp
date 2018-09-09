
/* Shape is an abstract class */
class Shape {
public:
	virtual void rotate(int) = 0;
	virtual void draw() const = 0;
	virtual bool is_closed() const = 0;
	virtual ~Shape();
};

class Point {
	int x;
	int y;
};

class Circle : public Shape {
public:
	void rotate(int) override {}
	void draw() const override;
	bool is_closed() const override { return true; }
	Circle(Point p, int r);
private:
	Point center;
	int radius;
};

// class Polygon : public Shape {
// public:
// 	bool is_closed() const override { return true; }

// };

// class Irregular_polygon : public Polygon {
// public:

// };

// Polygon b {p1, p2, p3, p4};

int main () {
	return 0;
}
