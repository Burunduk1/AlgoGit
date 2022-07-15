#include <bits/stdc++.h>

using namespace std;

template<class T> struct Graph {
	int n, s, t;
	struct Edge {
		int i;
		T f, c;
		int to;
		Edge* reverse;
	};
	vector<vector<Edge*>> g;
	vector<int> pos, h, gap;
	Graph(int n, int s, int t) : n(n), s(s), t(t), g(n), pos(n), h(n), gap(2 * n + 1) { }
	void add(int i, int a, int b, T c1, T c2 = 0) {
		g[a].push_back(new Edge {i, 0L, c1, b, 0});
		g[b].push_back(new Edge {-1, 0L, c2, a, g[a].back()});
		g[a].back()->reverse = g[b].back();
	}

	T dfs(int v, T flow) {
		if (v == t)
			return flow;
		T sum = 0;
		for (; pos[v] < (int)g[v].size(); pos[v]++) {
			auto &e = *g[v][pos[v]];
			if (h[v] == h[e.to] + 1 && e.c - e.f > 0) {
				auto df = dfs(e.to, min(e.c - e.f, flow - sum));
				sum += df;
				e.f += df;
				e.reverse->f -= df;
				if (sum == flow)
					return flow;
			}
		}
		if (--gap[h[v]] == 0)
			h[s] = n;
		++gap[++h[v]];
		pos[v] = 0;
		return sum;
	}

	T maxFlow() {
		T flow = 0;
		gap[0] = n;
		while (h[s] < n)
			flow += dfs(s, std::numeric_limits<T>::max());
		return flow;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	Graph<long long> g(n, 0, n - 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.add(i, a - 1, b - 1, c);
	}
	auto flow = g.maxFlow();
	cout << flow << "\n";
	vector<long long> ans(m);
	for (int v = 0; v < n; v++)
		for (auto e : g.g[v])
			if (e->i >= 0)
				 ans[e->i] = e->f;
	for (auto f : ans)
		cout << f << "\n";
}
