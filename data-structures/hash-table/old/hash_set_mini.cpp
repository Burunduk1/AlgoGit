template <const int max_size>
struct hashTable {
	ull hash[max_size];
	int size;

	int position( ull H ) const {
		int i = H % max_size;
		while (hash[i] && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}

	bool count( ull H ) const {
		return hash[position(H)] == H;
	}
	bool insert( ull H ) {
		ull &h = hash[position(H)];
		if (h == H)
			return 0;
		h = H, size++;
		assert(size <= max_size * 0.8);
		return 1;
	}
};
