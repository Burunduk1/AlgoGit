/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cassert>
#include <cmath>
#include <vector>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

struct Rational {
	int p, q;
	Rational() {}
	Rational(double x) {
		for (q = 1;; q++) {
			p = floor(x * q + 0.5);
			if (fabs((double)p / q - x) < 1e-6)
				break;
		}
	}
	double x() { return (double)p / q; }
};

// res(x[i]) = y[i] for all i=0..D-1
void interpolate(int D, int *x, int *y, Rational *res) {
	std::vector<double> f(D), add(D);
	forn(i, D) {
		double tmp = 0;
		for (int j = D - 1; j >= 0; j--)
			tmp = tmp * x[i] + f[j];
		tmp = y[i] - tmp;
		forn(j, i)
			tmp /= x[i] - x[j];
		add.assign(D, 0);
		add[0] = 1;
		forn(j, i) 
			for (int p = D - 1; p >= 0; p--)
				add[p] = (p ? add[p - 1] : 0) - x[j] * add[p];
		forn(j, D)
			f[j] += add[j] * tmp;
	}
	forn(i, D)
		res[i] = Rational(f[i]);
	forn(i, D) { // you may comment assertion-part
		double value = 0;
		for (int j = D - 1; j >= 0; j--)
			value = value * x[i] + f[j];
		assert(fabs(y[i] - value) <= 1e-6);
	}
}
