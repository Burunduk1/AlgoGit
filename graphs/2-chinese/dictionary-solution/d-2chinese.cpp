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
