/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

struct MinMaxHeap {
	vector<int> a; // i --> 2i, 2i+1, i/2
	MinMaxHeap() : a(1) { }

	void siftUpMin( int i ) {
		int x = a[i];
		while (i >= 4 && x < a[i / 4])
			a[i] = a[i / 4], i /= 4;
		a[i] = x;
	}
	void siftUpMax( int i ) { // differs from "siftUpMin" : change < to >
		int x = a[i];
		while (i >= 4 && x > a[i / 4])
			a[i] = a[i / 4], i /= 4;
		a[i] = x;
	}
	void siftUp( int i ) {
		if (i == 1)
			return;
		int level = 0, j = i;
		while (j > 1)
			j /= 2, level++;
		if ((level & 1) ^ (a[i] > a[i / 2]))
			level--, swap(a[i], a[i / 2]), i /= 2;
		if (level & 1)
			siftUpMax(i);
		else
			siftUpMin(i);
	}

	void add( int x ) {
		a.push_back(x);
		siftUp(a.size() - 1);
	}

	void siftDownMin( int i ) {
		if (i >= sz(a))
			return;
		while (4 * i + 3 < sz(a)) { // all grandchildren exist
			// ---> we may do only 3 comprassions instead of 4
			// int j0 = a[4 * i + 0] < a[4 * i + 1] ? 4 * i + 0 : 4 * i + 1;
			// int j1 = a[4 * i + 2] < a[4 * i + 3] ? 4 * i + 2 : 4 * i + 3;
			// int j = a[j0] < a[j1] ? j0 : j1;
			// if (a[j] == a[i])
			// 	return;
			int j = i;
			forn(t, 4)
				if (a[4 * i + t] < a[j])
					j = 4 * i + t;
			if (j == i)
				return;
			swap(a[i], a[j]), i = j;
		}
		int j = i, k;
		forn(t, 2)
			if ((k = 2 * i + t) < sz(a) && a[k] < a[j])
				j = k;
		forn(t, 4)
			if ((k = 4 * i + t) < sz(a) && a[k] < a[j])
				j = k;
		swap(a[i], a[j]);
		siftUp(j);
	}
	void siftDownMax( int i ) { // differs from "siftDownMin" : change < to >
		if (i >= sz(a))
			return;
		while (4 * i + 3 < sz(a)) { // all grandchildren exist
			int j = i;
			forn(t, 4)
				if (a[4 * i + t] > a[j])
					j = 4 * i + t;
			if (j == i)
				return;
			swap(a[i], a[j]), i = j;
		}
		int j = i, k;
		forn(t, 2)
			if ((k = 2 * i + t) < sz(a) && a[k] > a[j])
				j = k;
		forn(t, 4)
			if ((k = 4 * i + t) < sz(a) && a[k] > a[j])
				j = k;
		swap(a[i], a[j]);
		siftUp(j);
	}
	int getMin() {
		int result = a[1];
		a[1] = a.back();
		a.pop_back();
		siftDownMin(1);
		return result;
	}
	int getMax() {
		int i = 1;
		if (2 < sz(a) && a[2] > a[i]) i = 2;
		if (3 < sz(a) && a[3] > a[i]) i = 3;
		int result = a[i];
		a[i] = a.back();
		a.pop_back();
		siftDownMax(i);
		return result;
	}

	void out() {
		for (int i = 1; i < sz(a); i++) 
			printf("%d ", a[i]);
		puts("");
	}
	bool Assert( bool f ) {
		if (!f) {
			printf("failed: ");
			out();
			exit(1);
		}
	}
	void validate() {
		for (int i = 2; i < sz(a); i++) {
			int j = i, level = 0;
			while (j > 1)
				j /= 2, level++;
			for (j = i; j >= 1; j /= 2, level--)
				if (level & 1)
					Assert(a[j] >= a[i]);
				else
					Assert(a[j] <= a[i]);
		}
	}
};

int main() {
	MinMaxHeap h;
	char s[99];
	readWord(s);
	while (!seekEof()) {
		int x;
		readWord(s);
		if (!strcmp(s, "GetMin")) {
			writeInt(h.getMin(), '\n');
		} else if (!strcmp(s, "GetMax")) {
			writeInt(h.getMax(), '\n');
		} else {
			sscanf(strchr(s, '(') + 1, "%d", &x);
			h.add(x);
		}
		// h.validate();
	}
}
