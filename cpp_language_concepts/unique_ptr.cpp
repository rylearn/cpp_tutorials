
template<typename T, typename D = std::default_delete<T>>
class my_unique_ptr {
public:
	using pointer = ptr;
	using element_type = T;
	using deleter_type = D;
};
