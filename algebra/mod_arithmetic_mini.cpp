typedef long long ll;

const int MOD = 998244353;

struct Result {
    int x;
    Result(int x = 0) : x(x) { }
    Result operator + (Result r) const { return (x + r.x) % MOD; }
    Result operator * (Result r) const { return (ll)x * r.x % MOD; }
    Result& operator *= (Result r) { return *this = *this * r; }
    Result& operator += (Result r) { return *this = *this + r; }
};
