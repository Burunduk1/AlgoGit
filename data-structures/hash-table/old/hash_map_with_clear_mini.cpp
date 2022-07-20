template <const int max_size, class HashType, class Data, const Data default_value>
struct hashTable {
	HashType hash[max_size];
	Data f[max_size];
	int size, cc, used[max_size];

	hashTable()	{ size = 0, cc = 1; }
	void clear() { size = 0, cc++; }

	int position( HashType H ) const {
		int i = H % max_size;
		while (used[i] == cc && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}
	bool count( HashType H ) const { return hash[position(H)] == H; }

	Data & operator [] ( HashType H ) {
		int i = position(H);
		if (used[i] != cc)
			size++, hash[i] = H, used[i] = cc, f[i] = default_value;
		return f[i];
	}
};
