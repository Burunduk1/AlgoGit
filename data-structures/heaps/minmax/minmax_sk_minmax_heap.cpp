/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5;

struct MinMaxHeap {
	int n = 0, h[N];
	void add(int x) {
		h[++n] = x;
		int coef = 1;
		for (int i = n; i > 1; i /= 2)
			coef *= -1;
		int i = n;
		if (i > 1 && h[i / 2] * coef < h[i] * coef)
			swap(h[i / 2], h[i]), i /= 2, coef = -coef;
		for (; i >= 4 && h[i / 4] * coef > h[i] * coef; i /= 4)
			swap(h[i], h[i / 4]);
	}
	int del(int i, int coef) {
		swap(h[i], h[n--]);
		while (i <= n) {
			int opt = i, j;
			for (int t = 2; t <= 4; t *= 2)
				for (int s = 0; s < t; s++)
					if ((j = i * t + s) <= n && h[j] * coef < h[opt] * coef)
						opt = j;
			if (opt == i)
				break;
			swap(h[opt], h[i]), swap(i, opt);
			if (i >= opt * 4 && h[i / 2] * coef < h[i] * coef)
				swap(h[i], h[i / 2]);
		}
		return h[n+1];
	}
	int extractMin() {
		return del(1, 1);
	}
	int extractMax() {
		int i = (n == 1 ? 1 : (n >= 3 && h[3] > h[2] ? 3 : 2));
		return del(i, -1);
	}
} h;

int main() {
	char s[99];
	
	int n = readInt();
	while (n--) {
		readWord(s);
		if (s[0] == 'I') {
			int x = atoi(s + 7);
			h.add(x);
		} else if (s[4] == 'i') {
			writeInt(h.extractMin(), '\n');
		} else {
			writeInt(h.extractMax(), '\n');
		}
	}
}
