/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <algorithm>
#include <cstdio>

template<class T>
void hsort(T *a, int n) {
	T *b = a - 1; // b[1..n]
	auto down = [&](int v) {
		while (2 * v + 1 <= n) {
			int ma = (b[2 * v] > b[2 * v + 1] ? 2 * v : 2 * v + 1);
			if (b[ma] <= b[v])
				break;
			std::swap(b[v], b[ma]), v = ma;
		}
		if (2 * v <= n && b[2 * v] > b[v])
			std::swap(b[v], b[2 * v]);
	};
	for (int i = n; i >= 1; i--)
		down(i);
	while (n > 1)
		std::swap(b[n--], b[1]), down(1);
}
