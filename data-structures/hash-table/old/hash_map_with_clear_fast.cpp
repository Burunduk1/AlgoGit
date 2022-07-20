template <const int max_size, class Data, typename HashType>
struct hashTable {
	int cc, used[max_size];
	HashType hash[max_size];
	Data f[max_size];

	hashTable() { cc = 1; }
	void clear() { cc++; }

	inline int position( HashType H ) const {
		int i = H % max_size;
		while (used[i] == cc && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}

	inline bool is( int pos ) { return used[pos] == cc; }
	inline void add( HashType H, int pos, Data F ) { used[pos] = cc, hash[pos] = H, f[pos] = F; }
};

hashTable<(int)2e6 + 3, state, ull> d;
