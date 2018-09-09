
#include <memory>

class lval_box {
protected:
	int val;
	int low, high;
	bool changed {false};
public:
	lval_box(int ll, int hh) :val{ll}, low{ll}, high{hh} {}

	virtual int get_value() {
		changed = false;
		return val;
	}

	virtual void set_value(int i) {
		changed = true;
		val = i;
	}

	virtual void reset_value(int i) {
		changed = false;
		val = i;
	}

	virtual void prompt() {}

	virtual bool was_changed() const {
		return changed;
	}

	virtual ~lval_box() {};

};

class lval_slider : public lval_box {
private:
	// used to define what slider looks like
public:
	lval_slider(int, int);
	int get_value() override;
	void prompt() override;
}

void interact(lval_box* pb) {
	pb->prompt();
	int i = pb->get_value();
	if (pb -> was_changed()) {} 
	else {}
}

void some_fct() {
	unique_ptr<lval_box> p1 {new lval_slider{0, 5}};
	interact(p1.get());
}

int main() {
	return 0;
}
