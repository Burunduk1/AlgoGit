#include <random>
#include <algorithm>

template<class T>
void qsort(T *a, int l, int r) {
	if (l >= r)
		return;
	static std::mt19937 rnd(239);
	int i = l, j = r;
	//T x = a[l + rnd() % (r - l + 1)];
	T x = a[(l + r) / 2];
	while (i <= j) {
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j) std::swap(a[i++], a[j--]);
	}
	qsort(a, l, j);
	qsort(a, i, r);
}

template<class T>
void qsort(T *a, int n) {
	qsort(a, 0, n-1);
}
