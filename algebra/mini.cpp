typedef long double dbl;
typedef long long ll;

inline ll Mul(ll a, ll b, ll m) {
	ll k = (dbl)a * b / m;
	ll r = a * b - m * k;
	while (r < 0)	r += m;
	while (r >= m) r -= m;
	return r;
}

const int MOD = 1e9 + 7;
inline void add(int &a, int b) { if ((a += b) >= MOD) a -= MOD; }
inline void sub(int &a, int b) { if ((a -= b) < 0) a += MOD; }
inline int add(int a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
inline int sub(int a, int b) { if ((a -= b) < 0) a += MOD; return a; }
inline int mul(int a, int b) { return (ll)a * b % MOD; }
	
int Pow(int x, ll n) {
	int r = MOD > 1 ? 1 : 0;
	for (; n; n /= 2) {
		if (n & 1)
			r = mul(r, x);
		x = mul(x, x);
	}
	return r;
}
int Pow(int x, ll n) {
	if (n == 1)	return x;
	int y = Pow(x, n / 2);
	return (n & 1) ? mul(mul(y, y), x) : mul(y, y);
}

int Inv(int a) { return Pow(a, MOD - 2); }
int Div(int a, int b) { return mul(a, Inv(b)); }

int Euclid(int a, int b, int &x, int &y) { // a * x + b * y = gcd
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	int k = a / b, gcd = Euclid(b, a % b, x, y);
	swap(x, y), y -= k * x;
	return gcd;
}
int Inv(int a) { // x * a + y * MOD == 1
	int x, y, gcd = Euclid(MOD, a, y, x);
	return x < 0 ? x + M : x;
}

const int M = 1e6;
int pn, p[M];
void calc_primes() {
	for (int i = 2; i < M; i++)
		if (!p[i]) {
			p[pn++] = i;
			for (int j = i + i; j < M; j += i)
				p[j] = 1;
		}
}

void calc_c() {
	C[0][0] = 1;
	forn(i, N - 1)
		forn(j, N - 1)
			Add(C[i + 1][j], C[i][j]), Add(C[i + 1][j + 1], C[i][j]);
}
