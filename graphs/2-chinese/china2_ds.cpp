// Dmitry [cdkrot.me] Sayutin (2021)

#include <bits/stdc++.h>

using namespace std;

#define ALL(data)     data.begin(),data.end()

#include "china2_ds_2-chinese.cpp"

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	while (cin >> n >> m) {
		vector<vector<edge_t>> graph(n);
		map<pair<int,int>, pair<int, int>> min_edge; 
		for (int i = 0; i < m; i++) {
			int a, b, w;
			cin >> a >> b >> w, a--, b--;
			graph[a].push_back(edge_t {b, w});
			
			auto &e = min_edge[{a, b}];
			if (!e.second || e.first > w)
				e = {w, i + 1};
		}	
		arborescence arb(n, graph, 0);
		auto tree = arb.get_tree();

		cout << arb.ans << "\n";
		for (int a = 0; a < n; a++)
			for (auto b : tree[a]) {
				auto [w, i] = min_edge[{a, b}];
				cout << i << " ";
			}
		cout << "\n";
	}
}
