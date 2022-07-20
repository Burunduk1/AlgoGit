
template <const int max_size, class HashType, class Data, const Data default_value>
struct hashTable {
	HashType hash[max_size];
	Data f[max_size];
	int size, cc, used[max_size];

	hashTable() {
		cc = 1, size = 0;
	}

	void clear() {
		cc++, size = 0;
	}

	int position( HashType H ) const {
		int i = H % max_size;
		while (used[i] == cc && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}

	Data & operator [] ( HashType H ) {
		int i = position(H);
		if (used[i] != cc)
			size++, hash[i] = H, used[i] = cc;
		return f[i];
	}

	bool count( HashType H ) const {
		return used[position(H)] == cc;
	}
	
	Data get( HashType H ) const {
		int i = position(H);
		return used[i] == cc ? default_value : f[i]; 
	}
};

hashTable<2003, int, int, -1> h;
