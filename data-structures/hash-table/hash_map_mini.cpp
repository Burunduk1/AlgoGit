template<const int max_size = int(1e5 + 3), class HashType = int, class Data = int>
struct hashTable {
	HashType hash[max_size];
	Data f[max_size];
	int size;

	int position(HashType H) const {
		int i = H % max_size; // may cause TLE if H1, H2, H3.... form a long segment
		while (hash[i] && hash[i] != H) // H != 0
			if (++i == max_size)
				i = 0;
		return i;
	}

	Data& operator [] (HashType H) {
		int i = position(H);
		if (!hash[i])
			hash[i] = H, size++;
		return f[i];
	}
};

/* Usage */

hashTable h1; // can be used only as global variable (need arrays of zeroes inside)
hashTable<int(2e6+3), long long, char*> h2;
