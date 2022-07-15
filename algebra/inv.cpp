#include <vector>

// calculates inverses for 1..n-1 mod p in O(n)
std::vector<int> precalc(int p, int n) {
	std::vector<int> inv(n);
	inv[1] = 1;
	for (int i = 2; i < n; i++) 
		inv[i] = ((long long)(p - inv[p % i]) * (p / i)) % p;
	return inv;
}
