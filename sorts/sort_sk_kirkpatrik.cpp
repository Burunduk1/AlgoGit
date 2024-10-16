#include <vector>
#include <iostream>
#include <unordered_map>

#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

vector<int> cnt, pos, a1;

void ksort(vector<int> &a, int c) {
	int M = 1 << c, n = a.size();
	if (n <= 1) return;
	if (M <= n) {
		cnt.assign(M + 1, 0);
		pos.assign(M + 1, 0);
		for (int x : a) cnt[x]++;
		forn(i, M) pos[i + 1] = pos[i] + cnt[i];
		a1.resize(n);
		for (int x : a)	a1[pos[x]++] = x;
		copy(all(a1), a.begin());
		return;
	}
	int c1 = (c + 1) / 2;
	unordered_map<int, vector<int>> bs(n);
	for (int x : a) {
		int A = x >> c1, B = x & ((1 << c1) - 1);
		bs[A].push_back(B);
	}
	vector<int> as;
	as.reserve(n);
	for (auto &p : bs) {
		as.push_back(p.first);
		auto &B = p.second;
		int mi = 0;
		forn(i, B.size())
			if (B[i] > B[mi])
				mi = i;
		swap(B[mi], B.back());
		int tmp = B.back();
		B.pop_back();
		ksort(B, c1);
		B.push_back(tmp);
	}
	ksort(as, c1);
	int i = 0;
	for (auto A : as)
		for (auto B : bs[A])
			a[i++] = (A << c1) + B;
}

int main() {
	int n = readInt();
	vector<int> a(n);
	for (int &x : a) x = readInt();
	int m = *max_element(all(a));
	int c = 0;
	while ((1 << c) <= m)
		c++;
	ksort(a, c);
	for (int x : a)
		writeInt(x, ' ');
	writeChar('\n');
}
