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

	int ancestor(int j) {
		while ((j & 1) == r[j >> 1]) // пока мы -- левый сын
			j >>= 1;
		return j >> 1;
	}

	WeakHeap(vector<int> &_a) : a(_a) { // construct heap in O(n)
		r.assign(sz(a), 0);
		for (int i = sz(a) - 1, j; i > 0; i--)
			if (a[j = ancestor(i)] > a[i]) 
				swap(a[j], a[i]), r[i] ^= 1;
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
	vector<int> a(n);
	for (int &x : a) x = readInt();
	WeakHeap h(a);
	while (n--)
		writeInt(h.a[0], ' '), h.emin();
}
