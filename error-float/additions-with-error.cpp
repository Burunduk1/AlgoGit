/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cmath>
#include <cstdio>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
	const int n = 1e7;
	const double add = 3e-16;
	double x = 1, y = 1 + n * add;
	forn(i, n)
		x += add;
	printf("%.20f\n", x);
	printf("%.20f\n", y);
	printf("%g\n", abs(x / y - 1));
	printf("%g\n", 3e-16 * n);
}
