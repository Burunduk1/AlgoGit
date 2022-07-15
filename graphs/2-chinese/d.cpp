/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()
#define pb push_back 
#define all(a) (a).begin(), (a).end()

typedef vector <int> vi;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;
	vector<string> s(n);
	forn(i, n) cin >> s[i];
	forn(i, n) forn(j, n) if (i != j && s[i].find(s[j]) != string::npos) {
		s.erase(s.begin() + j);
		n--, i = 0, j = -1;
	}
	
	vector<vi> c(n, vi(n));
	vector<vi> pos(n, vi(n));
	forn(i, n)               
		forn(j, n) {
			c[i][j] = -1;
			for (int t = 0; t < sz(s[i]); t++) {
				int lcp = 0;
				while (t + lcp < sz(s[i]) && s[i][t + lcp] == s[j][lcp])
					lcp++;
				if (lcp > c[i][j])
					c[i][j] = lcp, pos[i][j] = t;
			}
		}
		
	/** 2-Chinese algorithm (Edmonds algorithm) */
	struct edge {
		int v, cost, i;
		bool operator < ( edge e ) const { return cost < e.cost; }
	};
	typedef vector<edge> v_edge;
	function<v_edge(const vector<v_edge>&)> solve = [&solve]( const vector<v_edge> &graph ) {
		int n = sz(graph);
		v_edge e(n);
		forn(i, n)
			if (graph[i].empty())
				e[i] = {-1, -1, -1};
			else
				e[i] = *min_element(all(graph[i]));
		vector<vi> cycles;
		vi color(n + 1), used(n + 1, -1);
		forn(i, n + 1) color[i] = i;
		used[n] = -2;
		forn(i, n)
			if (used[i] == -1 && e[i].v != -1) {
				int j = i;	
				while (used[j] == -1)
					used[j] = i, j = e[j].v;
				if (used[j] == i) { 
					vi cycle(1, j);
					for (int k = e[j].v; k != j; k = e[k].v)
						cycle.pb(k), color[k] = j;
					cycles.pb(cycle);
				}
			}
		if (cycles.empty())
			return e;
		vector<v_edge> new_graph(n);
		forn(v, n)
			for (auto edge : graph[v])
				if (color[edge.v] != color[v])
					new_graph[color[v]].pb({color[edge.v], edge.cost - e[v].cost, edge.i});
		v_edge tree = solve(new_graph);
		for (auto &cycle : cycles) {
			int c = color[cycle.back()];
			int from = -1;
			edge out = tree[c], new_out;
			assert(out.v != -1);
			for (int v : cycle) {
				for (edge e : graph[v])
					if (e.i == out.i)
						from = v, new_out = e;
				tree[v] = e[v];
			}
			assert(from != -1);
			tree[from] = new_out;
		}
		return tree;
	};
	vector<v_edge> graph(n);
	forn(i, n)
		forn(j, n)
			if (i != j)
				graph[j].pb(edge {i, -c[i][j], i * n + j});
	forn(i, n)
		graph[i].pb(edge {n, int(1e9), -i - 1});
	vi res(n, -1);
	for (auto e : solve(graph))
		if (e.i >= 0)
			res[e.i % n] = e.i / n;
	/** END */
		
	int vn = 1, len = 1;
	forn(i, n) {
		len += sz(s[i]);
		if (res[i] != -1)
			len -= c[res[i]][i];
	}
	printf("%d\n", len);
	vector<int> used(n, 0), path[n];
	printf("0\n");
	function<void(int)> out = [&]( int v ) {
		if (v == -1 || used[v]) return;
		used[v] = 1;
		out(res[v]);
		auto &P = path[v];
		if (res[v] == -1) {
			P.pb(vn);
			for (char c : s[v])
				printf("%d %c\n", P.back(), c),	P.pb(++vn);
		} else {
			int u = res[v];
			forn(i, c[u][v] + 1)
				P.pb(path[u][pos[u][v] + i]);
			for (int i = c[u][v]; i < sz(s[v]); i++)
				printf("%d %c\n", P.back(), s[v][i]), P.pb(++vn);
		}			
	};
	forn(i, n)
		out(i);
}
