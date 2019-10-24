/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <iostream>
#include <iterator>

#include "../testing/launch.cpp"
#include "qsort.cpp"
#include "msort.cpp"

using namespace std;

struct Test {
	vector<int> a;
	Test(int n) : a(n) {
		mt19937 rnd;
		for (int &x : a)
			x = rnd();
	}
	void out() {
		copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")), cout << endl;
	}
};

struct Solution {
	typedef void (*SortFunction)(int*, int);
	SortFunction f;
	const char *name;
	void operator() (Test &t) {
		f(t.a.data(), t.a.size());
	}
};

int main() {
	int n;
	cin >> n;

	Test t(n);
	testTL(t, Solution {qsort<int>, "quick sort"});
	testTL(t, Solution {msort<int>, "merge sort"});
}
