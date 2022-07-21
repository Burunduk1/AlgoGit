#include <cstdio>
#include <string>

// output numbers upto 10^{38}

void out(__int128 ans) {
	using ull = unsigned long long;
	static const ull x = 1e19;
	ull lower = ans % x;
	if (ans == lower)
		printf("%llu\n", lower);
	else
		printf("%llu%019llu\n", (long long)(ans / x), lower);
}

std::string str(__int128 ans) {
	using ull = unsigned long long;
	static const ull x = 1e19;
	ull lower = ans % x;
	char s[48];
	if (ans == lower)
		sprintf(s, "%llu\n", lower);
	else
		sprintf(s, "%llu%019llu\n", (long long)(ans / x), lower);
	return s;
}

int main() {
	__int128 x = 1;
	for (int i = 0; i <= 38; i++) {
		out(x);
		printf("%s\n", str(x).c_str());
		x *= 10;
	}
}
