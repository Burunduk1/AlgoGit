template<const int MAX_SIZE>
struct HashMap {
	int hash[MAX_SIZE], f[max_size];

	int position(HashType H) const {
		int i = H % max_size;
		while (hash[i] && hash[i] != H) // H != 0
			if (++i == max_size)
				i = 0;
		return i;
	}
};

HashMap<(int)2e6 + 3> h;
