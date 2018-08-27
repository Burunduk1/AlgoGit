/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <vector>

using namespace std;

template<class T>
vector<int> zFunction( const T &s ) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = -1;
	for (int i = 1; i < n; i++) {
		int k = max(0, min(z[i - l], r - i));
		while (i + k < n && s[i + k] == s[k])
			k++;
		z[i] = k;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
