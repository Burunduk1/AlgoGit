// https://admin.contest.yandex.ru/submissions/117080254

#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
int add(int a, int b) { return (a + b) % MOD; }
int sub(int a, int b) { return (a - b + MOD) % MOD; }
int mul(int a, int b) { return (long long)a * b % MOD; }
int pw(int a, int n) { 
	if (!n) return 1;
	int x = pw(a, n / 2);
	x = mul(x, x);
	return n % 2 ? mul(x, a) : x;
}
int div(int a, int b) { return mul(a, pw(b, MOD - 2)); }

vector<int> berlekampMassey(vector<int> s) {
	int n = s.size();
	int L = 0, m = 0, b = 1;
	vector<int> C(n), B(n); // ans = C[0]..C[L] 
	C[0] = B[0] = 1;
	for (int i = 0; i < n; ++i) {
		++m;
		int d = s[i]; // C[0] = 1, just optimization
		for (int j = 1; j <= L; ++j) {
			d = add(d, mul(C[j], s[i - j]));
		}
		if (!d)
			continue;
		auto C_ = C; // save version before modification
		int coef = div(d, b);
		for (int j = m; j < n; ++j)
			C[j] = sub(C[j], mul(coef, B[j - m]));
		if (2 * L <= i)
			L = i + 1 - L, B = C_, b = d, m = 0;
	}
	// we have C(x) = x^k - \sum_i x^{k-i} f_i : now we wanna recover f_i
	C.resize(L + 1);
	C.erase(C.begin());
	for (int& x : C)
		x = sub(0, x);
	return C;
}
