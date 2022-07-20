template<const int MAX_SIZE = int(1e5 + 3), class HashType = int, class Data = int> // DEFAULT_VALUE = Data()
struct HashMap {
	HashType hash[MAX_SIZE];
	Data f[MAX_SIZE];
	int size, cc, used[MAX_SIZE];

	HashMap() { size = 0, cc = 1; }
	void clear() { size = 0, cc++; }

	int position(HashType H) const {
		int i = H % MAX_SIZE; // may cause TLE if H1, H2, H3.... form a long segment
		while (used[i] == cc && hash[i] != H)
			if (++i == MAX_SIZE)
				i = 0;
		return i;
	}
	bool count(HashType H) const { 
		return hash[position(H)] == H; 
	}

	Data& operator [] (HashType H) {
		int i = position(H);
		if (used[i] != cc)
			size++, hash[i] = H, used[i] = cc; //, f[i] = Data(); // DEFAULT_VALUE
		return f[i];
	}
};

/* Usage */

#include <iostream>
#include <string>

using namespace std;

HashMap h; // can be used only as global variable (need arrays of zeroes inside)
HashMap<int(2e6+3), int64_t, string> h2; // string literal cannot be used as a template argument => DEFAULT_VALUE not in template args

int main() {
	cout << h.count(3) << endl;
	cout << h[3] << endl;
	cout << h.count(3) << endl;
	h[3] = 13;
	cout << h[3] << endl;

	cout << h2.count(1e18) << endl;
	cout << h2[1e18] << endl;
	cout << h2.count(1e18) << endl;
	h2[3] = "smth";
	cout << h2[1e18] << endl;
}
