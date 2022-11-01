/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <vector>
#include "optimization.h" // http://acm.math.spbu.ru/~sk1/algo/lib/optimization.h.html

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

struct WeakHeap {
	vector<int> a, r;

	WeakHeap(int n) { a.reserve(n), r.reserve(n); }

	int ancestor(int j) {
		while ((j & 1) == r[j >> 1]) // пока мы -- левый сын
			j >>= 1;
		return j >> 1;
	}

	void add(int x) { // O(logn)
		a.push_back(x), r.push_back(0);
		for (int i = sz(a) - 1, j; i > 0 && (a[j = ancestor(i)] > a[i]); i = j) 
			swap(a[j], a[i]);
	}

	void emin() {
		int i, j, x = a.back();
		a.pop_back(), r.pop_back();
		if (!sz(a)) 
			return;
		for (i = 1; (j = 2 * i + r[i]) < sz(a); i = j)
			;
		for (; i >= 1; i /= 2) 
			if (x > a[i]) 
				swap(a[i], x), r[i] ^= 1;
		a[i] = x;
	}
};

int main() {
	int n = readInt();
	WeakHeap h(n);
	while (n--)
		h.add(readInt());
	while (h.a.size())
		writeInt(h.a[0], ' '), h.emin();
}
