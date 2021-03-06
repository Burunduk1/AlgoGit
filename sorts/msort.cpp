/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <vector>
#include <algorithm>

template<class T>
void msort(T *a, int l, int r, T *buf) {
	if (l >= r)
		return;
	int m = l + (r - l) / 2;
	msort(a, l, m, buf);
	msort(a, m+1, r, buf);

	int i = l, j = m+1;
	for (int k = l; k <= r; k++)
		if (i <= m && (j > r || a[i] <= a[j]))
			buf[k] = a[i++];
		else
			buf[k] = a[j++];
	std::copy(buf + l, buf + r + 1, a + l);
}

template<class T>
void msort_insertion(T *a, int l, int r, T *buf) {
	if (l + 10 >= r) {
		for (int i = l + 1; i <= r; i++) {
			int j = i;
			while (j > l && a[j-1] > a[j])
				std::swap(a[j], a[j-1]), j--;
		}
		return;
	}

	int m = l + (r - l) / 2;
	msort_insertion(a, l, m, buf);
	msort_insertion(a, m+1, r, buf);

	int i = l, j = m+1;
	for (int k = l; k <= r; k++)
		if (i <= m && (j > r || a[i] <= a[j]))
			buf[k] = a[i++];
		else
			buf[k] = a[j++];
	std::copy(buf + l, buf + r + 1, a + l);
}

template<class T> void msort(T *a, int n) {
	std::vector<T> buf(n);
	msort(a, 0, n-1, buf.data());
}

template<class T> void msort_insertion(T *a, int n) {
	std::vector<T> buf(n);
	msort(a, 0, n-1, buf.data());
}
