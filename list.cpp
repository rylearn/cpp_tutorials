
template<class T>
class List {
public:
	void insert(T);
	T get();

private:
	struct Link { T val; Link* next; };

	struct Chunk {
		enum { chunk_size = 15 };
		Link v[chunk_size];
		Chunk* next;
	};

	Chunk* allocated;
	Link* free;
	Link* get_free();
	Link* head;
};