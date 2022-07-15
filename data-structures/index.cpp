// 0-based auto index
template<class T>
struct AutoIndex : map<T, int> { // unordered_map<T, int>
	int get(const T &item) {
		int &r = (*this)[item];
		return (r ? r : (r = this->size())) - 1;
	}
};
