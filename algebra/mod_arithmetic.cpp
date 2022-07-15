#include <vector>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct Result {
    int x;
    Result(int x = 0) : x(x) { }
    Result operator + (Result r) const { 
    	int y = x + r.x;
    	return y >= MOD ? y - MOD : y;
    }
    Result operator - (Result r) const { 
    	int y = x - r.x;
    	return y < 0 ? y + MOD : y;
    }
    Result operator * (Result r) const { return (ll)x * r.x % MOD; }
    Result operator - () const { return x ? MOD - x : 0; }

    Result& operator += (Result r) { return *this = *this + r; }
    Result& operator *= (Result r) { return *this = *this * r; }
    Result& operator -= (Result r) { return *this = *this - r; }

    Result power(int n) {
    	Result r = 1, a = x;
    	for (; n; n /= 2) {
    		if (n & 1)
    			r *= a;
    		a *= a;
    	}
    	return r;
    }
    Result inv() { return power(MOD - 2); }
};

namespace precalc {
	struct inv {
		vector<Result> a;
		inv(int n) : a(n) {
			for (size_t i = 2; i < a.size(); i++) 
				a[i] = -Result(MOD / i) * a[MOD % i];
		}
		Result operator[] (int i) const { return a[i]; }
	};
	struct C {
		vector<vector<Result>> a;
		C(int n) : a(n, vector<Result>(n)) {
			a[0][0] = 1;
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - 1; j++)
					a[i + 1][j] += a[i][j], a[i + 1][j + 1] += a[i][j];
				a[i + 1][n - 1] += a[i][n - 1];
			}
		}
		Result get(int i, int j) { return a[i][j]; }
	};
}
