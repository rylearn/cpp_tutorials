#include <iostream>
using namespace std;

class Date {

	int d, m, y;
	// static Date default_date;

public:
	explicit Date(int dd =0, int mm =0, int yy =0);
	static void set_default(int dd, int mm, int yy);

	int year() const {
		return y;
	}

	int month() const {
		return m;
	}				

	int day() const {
		return d;
	}

	// add n years to y
	void add_year(int n) {
		y += n;
	}

	// add n years to m				
	void add_month(int n) {
		m += n;
	}				

	// add n years to d
	void add_day(int n) {
		d += n;
	}
};

ostream& operator<<(ostream& os, const Date& d) {
	return os << d.month() << "/" << d.day() << "/" << d.year();
}

Date::Date(int dd, int mm, int yy)
{
	d = dd;
	m = mm;
	y = yy;
}

Date my_birthday;

void f()
{
	Date today {16, 10, 1996};
	my_birthday = Date {30, 12, 1950};

	Date tomorrow = today;
	tomorrow.add_day(1);
}

int main() {
	Date d1 {15, 23};
	cout << d1 << endl;

	return 0;
}

