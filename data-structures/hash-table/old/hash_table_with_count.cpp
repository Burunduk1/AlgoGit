// Note: HASH can not be equal to 0

/* Common template */

#include <cstring>
#include <cstdio>

#define zero(a) memset(a, 0, sizeof(a))

typedef long long ll;

/* Main part */

template <const int maxh>
class hashTable {
	ll hash[maxh];
	int cnt[maxh];
	int size;

private: 
	inline int position( ll H ) {
		int i = H % maxh;
		while (hash[i] && hash[i] != H)
			if (++i == maxh)
				i = 0;
		return i;
	}

public:
	hashTable() {
		zero(hash);
		zero(cnt);
		size = 0;
	}

	void add( ll H, int d ) {
		int i = position(H);
		if (cnt[i] == 0 && d != 0)
			size++, hash[i] = H;
		cnt[i] += d;
		if (cnt[i] == 0)
			size--;
	}

	int getSize() { return size; }
	int count( ll H ) { return cnt[position(H)]; }
};

int main() {
	hashTable<103> table;

	table.add(10, 2);
	table.add(10, -3);
	table.add(9, 1);
	printf("count[10] = %d, size = %d\n", table.count(10), table.getSize());
	return 0;
}
