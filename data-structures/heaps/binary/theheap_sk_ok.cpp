/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

struct Heap {
	vector<int> h;
	Heap() : h(1, INT_MIN) { }
	void add(int x) {
		int i = h.size();
		h.push_back(-1);
		for (; h[i / 2] > x; i /= 2)
			h[i] = h[i / 2];
		h[i] = x;
	}
	int getMin() {
		int res = h[1], n = h.size() - 1;
		swap(h[1], h.back()), h.pop_back();
		for (int i = 1, m; 2 * i < n; i = m) {
			m = 2 * i + (2 * i + 1 < n && h[2 * i] > h[2 * i + 1]);
			if (h[i] <= h[m]) break;
			swap(h[i], h[m]);
		}
		return res;
	}
} h;

int main() {
	for (int n = readInt(); n; n--)
		if (readChar() == '+')
			h.add(readInt());
		else 
			writeInt(h.getMin(), '\n');
}
