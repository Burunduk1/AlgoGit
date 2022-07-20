template <const int max_size>
struct hashTable {
	int cc, u[max_size];
	int hash[max_size];

	hashTable() : cc(1) { }
	void clear() { cc++; }

	int position( int H ) const {
		int i = H % max_size;
		while (u[i] == cc && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}

	bool count( int H ) const {
		return u[position(H)] == cc;
	}
	bool insert( int H ) {
		int i = position(H);
		if (u[i] == cc)
			return 0;
		u[i] = cc, hash[i] = H;
		return 1;
	}
};
