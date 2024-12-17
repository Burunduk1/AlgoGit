#include <vector>
#include <cstring>
#include <iostream>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5;
const int P = 123456, MOD = 1e9 + 7;

char s[N+1], rs[N+1], com[30];

struct Hash {
	int h, degP;
	Hash operator + (Hash a) {
		return {(int)(((int64_t)h * a.degP + a.h) % MOD), (int)((int64_t)degP * a.degP % MOD)};
	}
};

struct Tree {
	int n;
	vector<Hash> h;
	Tree(int n, const char *s) : n(n), h(2 * n) {
		forn(i, n)
			h[i + n] = {s[i], P};
		for (int i = n - 1; i; i--)
			h[i] = h[2 * i] + h[2 * i + 1];
	}
	void change(int i, char c) {
		h[i += n] = {c, P};
		for (i /= 2; i; i /= 2)
			h[i] = h[2 * i] + h[2 * i + 1];
	}
	int get(int l, int len) {
		int r = l + len - 1;
		Hash hl {0, 1}, hr {0, 1};
		for (l += n, r += n; l <= r; l /= 2, r /= 2) {
			if (l % 2 == 1) hl = hl + h[l++];
			if (r % 2 == 0) hr = h[r--] + hr;
		}
		return (hl + hr).h;
	}
};

int main() {
	readWord(s);
	int n = strlen(s);
	forn(i, n)
		rs[n - i - 1] = s[i];
	Tree t(n, s), rt(n, rs);
	for (int m = readInt(); m; m--) {
		readWord(com);
		if (com[0] == 'p') {
			int l = readInt() - 1;
			int r = readInt();
			writeWord(t.get(l, r - l) == rt.get(n - r, r - l) ? "Yes\n" : "No\n");
		} else {
			int i = readInt() - 1;
			char c = readChar();
			t.change(i, c);
			rt.change(n - i - 1, c);
		}
	}
}
