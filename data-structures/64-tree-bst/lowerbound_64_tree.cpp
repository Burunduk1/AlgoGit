#include <vector>
#include <cstdint>
#include <bit>

using namespace std;

const uint32_t INFTY = -1;

// bst for [0,2^32) ; space ~= 500mb
struct Tree {
	vector<vector<uint64_t>> a;

	void add(uint32_t x) {
		for (auto &b : a)
			b[x / 64] |= 1ull << (x % 64), x /= 64;
	}

	Tree() {
		for (auto x = INFTY; x > 0; x /= 64)
			a.push_back(vector<uint64_t>(x / 64 + 1));
		add(INFTY);
	}

	uint32_t lowerBound(uint32_t x) {
		int i = 0;
		while (!(a[i][x / 64] >> (x % 64)))
			x /= 64, i++, x++;
		x += countr_zero(a[i][x / 64] >> (x % 64));
		while (i > 0)
			x *= 64, x += countr_zero(a[--i][x / 64]);
		return x;
	}
};
