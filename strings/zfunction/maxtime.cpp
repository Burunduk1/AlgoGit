/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cstdio>
#include <cassert>
#include <string>

#include "algo-zfunction.cpp"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

struct Timer {
	double ticks;
	Timer() : ticks(0) { }
	void start() {
		ticks = clock();
	}
	double sec() {
		return (clock() - ticks) / CLOCKS_PER_SEC;
	}
	void print( const char *s = 0 ) {
		printf("%.3f : %s\n", sec(), s ? s : "");
	}
} t;

void launch( const vector<int> &test, const char *s = 0 ) {
	t.start();
	zFunction(test);
	t.print(s);
}

int main() {
	const int N = 1e7;
	printf("N = %d\n", N);
	vector<int> test(N, 1);
	test.push_back(2);
	launch(test, "aaaaaaab");
	test[N / 2] = 2;
	launch(test, "aaabaaab");
	for (auto &x : test) x = rand() % 2;
	launch(test, "random");
}
