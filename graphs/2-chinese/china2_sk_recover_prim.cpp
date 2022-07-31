/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 2e8
#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

#include "china2_sk_recover_prim_2-chinese.cpp"

void solve() {
	int n = readInt();
	int m = readInt();
	Solver s(n);
	forn(i, m) {
		// edge: a ---> b, weight=w
		int a = readInt() - 1;
		int b = readInt() - 1;
		int w = readInt();
		s.addEdge(a, b, w); // auto index given edges
	}
	s.run();
	writeInt(s.sum_w, '\n');
	for (int i : s.ans)
		writeInt(i + 1, ' ');
	writeChar('\n');
}

int main() {
	while (!seekEof())
		solve(), allocator_pos = 0; // free all the memory 
}
