#include <algorithm>

using namespace std;

const int MOD = 998244353;
void add(int &a, int b) { if ((a += b) >= MOD) a -= MOD; }
int mul(int a, int b) { return (int64_t)a * b % MOD; }

const int N = 2e6 + 3;
int inv[N];

void precalc() {
	inv[1] = 1;
	for (int i = 2; i < N; i++) 
		inv[i] = ((int64_t)(MOD - inv[MOD % i]) * (MOD / i)) % MOD;
}

struct C {
	int n, k, r;
	C(int n = 0, int k = 0, int r = 1) : n(n), k(k), r(r) { }
	void dn() { // n++
		r = mul(r, ++n);
		r = mul(r, inv[n - k]);
	}
	void dk() { // k++
		r = mul(r, n - k++);
		r = mul(r, inv[k]);
	}
};

int main() {
	precalc();

	C x;
	x.dn();
	x.dk();
}
