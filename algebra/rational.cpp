#include <algorithm>
#include <cassert>

typedef long long ll;

struct num {
	ll a, b;

	num(ll a = 0, ll b = 1) : a(a), b(b) { norm(); }

	void norm() {
		ll g = std::__gcd(a, b);
		assert(b);
		a /= g, b /= g;
		if (b < 0)
			a = -a, b = -b;
	}

	num operator + (num x) { return num(a * x.b + b * x.a, x.b * b); }
	num operator - (num x) { return num(a * x.b - b * x.a, x.b * b); }
	num operator * (num x) { return num(a * x.a, b * x.b); }
	num operator / (num x) { return num(a * x.b, b * x.a); }
	num operator ~ () { return num(b, a); }
	bool operator ! () { return a == 0; }

	bool operator == (num x) { return a * x.b - b * x.a == 0; }
	bool operator != (num x) { return a * x.b - b * x.a != 0; }
	bool operator < (num x) { return a * x.b - b * x.a < 0; }
	bool operator > (num x) { return a * x.b - b * x.a > 0; }

	// += -= *= /=
	#define DECLARE(s) \
		num& operator s##= (num x) { return *this = (*this s x); }
	DECLARE(+) 
	DECLARE(-)
	DECLARE(*)
	DECLARE(/)
};
