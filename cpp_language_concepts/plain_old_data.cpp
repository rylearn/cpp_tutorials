
struct Company {};

struct Role {};

struct ChiefExecutive : Role {
	double salary;
};

template<typename T>
void mycopy(T* to, const T* from, int count) {
	if (is_pod<T>::value)
		memcpy(to, from, count * sizeof(T));
	else
		for (int i = 0; i != count; ++i)
			to[i] = from[i];
}

int main () {
	ChiefExecutive you = ChiefExecutive();
	
	return 0;
}