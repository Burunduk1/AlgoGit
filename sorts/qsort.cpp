/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <random>
#include <algorithm>

template<class T>
void qsort(T *a, int l, int r) {
	if (l >= r)
		return;
	int i = l, j = r;
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
void qsort_insertion(T *a, int l, int r) {
	if (l + 10 >= r) {
		for (int i = l + 1; i <= r; i++) {
			int j = i;
			while (j > l && a[j-1] > a[j])
				std::swap(a[j], a[j-1]), j--;
		}
		return;
	}
	int i = l, j = r;
	T x = a[(l + r) / 2];
	while (i <= j) {
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j) std::swap(a[i++], a[j--]);
	}
	qsort_insertion(a, l, j);
	qsort_insertion(a, i, r);
}

template<class T>
void qsort_random(T *a, int l, int r) {
	if (l >= r)
		return;
	static std::mt19937 rnd(239);
	int i = l, j = r;
	T x = a[l + rnd() % (r - l + 1)];
	while (i <= j) {
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j) std::swap(a[i++], a[j--]);
	}
	qsort_random(a, l, j);
	qsort_random(a, i, r);
}

template<class T> void qsort(T *a, int n) {	
	qsort(a, 0, n-1); 
}
template<class T> void qsort_insertion(T *a, int n) {	
	qsort_insertion(a, 0, n-1); 
}
template<class T> void qsort_random(T *a, int n) {	
	qsort_random(a, 0, n-1); 
}
