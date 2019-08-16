// this is debug version
// release version: asserts should be off

#include <cassert>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

typedef unsigned long long ull;

struct Bitset {
	int n;
	vector<ull> data;
	void init(int _n) {	data.assign(n = _n / 64 + 1, 0); }
	Bitset(int n = 0) { init(n); }
	bool contains(const Bitset &b) const {
		assert(n >= b.n);
		forn(i, b.n)
			if ((data[i] & b.data[i]) != b.data[i])
				return 0;
		return 1;
	}
	Bitset& operator |= (const Bitset &b) {
		assert(n >= b.n);
		forn(i, b.n)
			data[i] |= b.data[i];
		return *this;
	}
	int operator [] (int i) {
		assert(0 <= i && i < n * 64);
		return (data[i / 64] >> (i & 63)) & 1;
	}
	void set(int i) {
		assert(0 <= i && i < n * 64);
		data[i / 64] |= 1ULL << (i & 63);
	}
	void zero(int i) {
		assert(0 <= i && i < n * 64);
		data[i / 64] &= ~(1ULL << (i & 63));
	}
};
