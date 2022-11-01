/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

const int maxN = 1e5;

struct Heap {
	int n, h[maxN + 1];
	void add( int x ) {
		h[++n] = x;
		for (int i = n; i > 1 && h[i >> 1] > h[i]; i >>= 1) 
			swap(h[i], h[i >> 1]);
	}
	int down( int v ) {
		while (1) {
			int l = 2 * v;
			if (l < n && h[l + 1] < h[l]) l++;
			if (l > n || h[l] >= h[v]) break;
			swap(h[l], h[v]), v = l;
		}
		return v;
	}
	int pop() {
		swap(h[1], h[n--]);
		down(1);
		return h[n + 1];
	}
	int min() { return n ? h[1] : INT_MAX; }
};

Heap mi, mi_del;
Heap ma, ma_del;
#define SKIP(a, b) while (b.min() == a.min()) a.pop(), b.pop();

int main() {
	char s[99];
	readLine(s);
	while (readLine(s)) {
		if (s[0] == 'I') {
			int x = atoi(s + 7);
			mi.add(x);
			ma.add(-x);
		} else if (s[4] == 'i') {
			SKIP(mi, mi_del);
			int x = mi.pop();
			writeInt(x, '\n');
			ma_del.add(-x);
		} else {
			SKIP(ma, ma_del);
			int x = -ma.pop();
			writeInt(x, '\n');
			mi_del.add(x);
		}
	}
}
