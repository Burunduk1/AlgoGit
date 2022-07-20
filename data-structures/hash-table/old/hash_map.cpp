/* Common template */

#include <cstring>
#include <cstdio>

typedef long long ll;

/* Main part */

template <const int max_size, class Data, const Data default_value>
struct hashTable {
	ll hash[max_size];
	Data f[max_size];
	int size;

	int position( ll H ) const {
		int i = H % max_size;
		while (hash[i] && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}

	hashTable() {
		memset(hash, 0, sizeof(hash)), size = 0;
	}

	Data get( ll H ) const {
		int i = position(H);
		return hash[i] ? f[i] : default_value;
	}

	bool count( ll H ) const {
		return hash[position(H)];
	}

	Data & operator [] ( ll H ) {
		int i = position(H);
		if (!hash[i])
			hash[i] = H, f[i] = default_value, size++;
		return f[i];
	}

	void set( ll H, Data val ) { 
		(*this)[H] = val;
	}
};

/* Test */

int main()
{
	hashTable<103, int, -1> table;

	printf("get = %d, size = %d\n", table.get(10), table.size);
	table.set(9, 2);
	printf("get = %d, size = %d\n", table.get(9), table.size);
	return 0;
}
