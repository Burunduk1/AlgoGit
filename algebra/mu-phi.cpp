/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

vector<int> calc_mu(int n) {
	vector<int> mu(n+1);
	mu[1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 2 * i; j <= n; j += i)
			mu[j] -= mu[i];
	return mu;
}

vector<int> calc_phi(int n) {
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for (int i = 1; i <= n; i++)
		for (int j = 2 * i; j <= n; j += i)
			phi[j] -= phi[i];
	return phi;
}

void out(const vector<int> &a) {
	for (int x : a) cout << x << " ";
	cout << "\n";
}

int main() {
	out(calc_mu(30));
	out(calc_phi(30));
}
