
class Character_device {
public:
	virtual int open(int opt) = 0;
	virtual int close(int opt) = 0;
	virtual int read(char* p, int n) = 0;
	virtual int write(const char* p, int n) = 0;
	// virtual int ioctl(int ...) = 0;

	// virtual ~Character_device() {}
};

class Device1 : public Character_device {
public:
	int open(int opt) override {
		return 0;
	}

	int close(int opt) override {
		return 0;
	}

	int read(char* p, int n) override {
		return 0;
	}

	int write(const char* p, int n) override {
		return 0;
	}

	// int ioctl(int ...) override {
	// 	return 0;
	// }
};

int main () {
	Device1 someDevice = Device1();
	return 0;
}
