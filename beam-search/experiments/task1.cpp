/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 * 
 * Statment: go from (1,1) to (n,n) with right-up-moves, maximize sum under the path
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define err(...) fprintf(stderr, "%.2f : ", 1. * clock() / CLOCKS_PER_SEC), fprintf(stderr, __VA_ARGS__), fflush(stderr)

int main() {
	int n = 1000;

	forn(test, 100) {
	vector<vector<int>> a(n, vector<int>(n));
	forn(i, n)
		forn(j, n)
			a[i][j] = 1 + rand() % 10000;

	auto relax = [](int &a, int b) {
		a = max(a, b);
	};
	vector<vector<int>> dp(n+1, vector<int>(n+1));
	forn(i, n)
		forn(j, n) {
			dp[i][j] += a[i][j];
			relax(dp[i + 1][j], dp[i][j]);
			relax(dp[i][j + 1], dp[i][j]);
		}
	auto ans1 = dp[n - 1][n - 1];

	const int BEAM = 30;
	vector<tuple<int, int, int>> q = {{-a[0][0], 0, 0}}, q2;
	vector<vector<int>> used(n+1, vector<int>(n+1));
	forn(_, n + n - 2) {
		// err("q.size = %d\n", (int)q.size());
		sort(q.begin(), q.end());
		if ((int)q.size() > BEAM) q.resize(BEAM);
		q2.clear();
		for (auto [D, x, y] : q) {
			// err("relax from D=%d x=%d y=%d\n", D, x, y);
			if (x + 1 < n) relax(used[x + 1][y], -D);
			if (y + 1 < n) relax(used[x][y + 1], -D);
		}
		for (auto [D, x, y] : q) {
			auto add = [&](int zx, int zy) {
				q2.push_back({-(used[zx][zy] + a[zx][zy]), zx, zy});
				used[zx][zy] = 0;
			};
			if (x + 1 < n && used[x + 1][y]) add(x + 1, y);
			if (y + 1 < n && used[x][y + 1]) add(x, y + 1);
		}
		q.swap(q2);
	}
	assert(q.size());
	auto [D, x, y] = q[0];
	assert(x == n - 1 && y == n - 1);
	auto ans2 = -D;
	
	cout << ans1 << " " << ans2 << " " << (ans1 == ans2) << "\n";
	// assert(ans1 == ans2);
	}
}
