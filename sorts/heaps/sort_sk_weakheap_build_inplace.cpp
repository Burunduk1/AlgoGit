/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <vector>
#include "optimization.h" // http://acm.math.spbu.ru/~sk1/algo/lib/optimization.h.html

using namespace std;

int main() {
	int n = readInt();
	vector<int> a(n);
	for (int &x : a) x = readInt() << 1;
	auto ancestor = [&](int j) {
		while ((j & 1) == (a[j >> 1] & 1)) // пока мы -- левый сын
			j >>= 1;
		return j >> 1;
	};
	auto swap_ = [&](int &a, int &b) {
		int r = (a & 1) ^ (b & 1);
		swap(a, b), a ^= 1 ^ r, b ^= r;
	};
	for (int i = n - 1, j; i > 0; i--)
		if (a[j = ancestor(i)] > a[i])  
			swap_(a[i], a[j]);
	while (n--) {
		writeInt(a[0] >> 1, ' ');
		int i, j, x = a[n];
		if (!n) 
			break;
		for (i = 1; (j = 2 * i + (a[i] & 1)) < n; i = j)
			;
		for (; i >= 1; i /= 2) 
			if (x > a[i])
				swap_(a[i], x);
		a[i] = x;
	}
}
