#include <bits/stdc++.h>

using namespace std;

template<class T> struct Graph {
	int n, s, t;
	struct Edge {
		int i;
		T f, c;
		int to;
		Edge* reverse;
		void push(T df) { f += df, reverse->f -= df; }
	};
	vector<vector<Edge*>> g;
	vector<int> h, q;
	vector<T> ex;
	Graph(int n, int s, int t) : n(n), s(s), t(t), g(n), h(n), q(n), ex(n) { }
	void add(int i, int a, int b, T c1, T c2 = 0) {
		if (a == b) return;
		g[a].push_back(new Edge {i, 0L, c1, b, 0});
		g[b].push_back(new Edge {-1, 0L, c2, a, g[a].back()});
		g[a].back()->reverse = g[b].back();
	}

	void bfs(int start) {
		fill(h.begin(), h.end(), n);
		q.clear();
		q.push_back(start), h[start] = 0;
		for (int i = 0; i < (int)q.size(); i++) {
			int v = q[i], x;
			for (auto e: g[v])
				if (e->reverse->f < e->reverse->c && h[x = e->to] == n)
					q.push_back(x), h[x] = h[v] + 1;
		}
	}
	void push(int v, Edge* e, int df) {
		e->push(df), ex[v] -= df, ex[e->to] += df;
	}
	T maxFlow() {
		for (auto e: g[s])
			push(s, e, e->c);
		for (int _ = 0; _ < 2; _++) {
			for (bool run = 1; run; ) {
				run = 0;
				bfs(t);
				reverse(q.begin(), q.end());
				T df;
				for (int v : q) if (v != s)
					for (auto e: g[v]) 
						if (h[e->to] + 1 == h[v] && 0 < (df = min(ex[v], e->c - e->f)))
							run = 1, push(v, e, df);
			}
			swap(s, t);
		}
		return ex[t];
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
