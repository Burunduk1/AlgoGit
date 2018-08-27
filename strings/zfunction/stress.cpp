/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cstdio>
#include <cassert>
#include <string>

#include "algo-zfunction.cpp"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template <class T>
vector<int> slow( const T &s ) {
	int n = s.size();
	vector<int> z(n);
	for (int i = 1; i < n; i++) 
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
	return z;
}

int main() {
	int tn = 1000;
	for (int n = 5;; n *= 2) 
		for (int alpha = 2; alpha <= 4; alpha++) {
			printf("test n = %d, alpha = %d : [%d tests]\n", n, alpha, tn);
			forn(i, tn) {
				string s;
				forn(j, n)
					s += 'a' + rand() % alpha;
				auto ca = zFunction(s), ja = slow(s);
				// forn(i, s.size())
				// 	printf("%d : %d %d\n", i, ca[i], ja[i]);
				// printf("%s\n", s.c_str());
				assert(ca == ja);
			}
		}
}
