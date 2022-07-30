struct heap_node;
heap_node* merge(heap_node* a, heap_node* b);

struct heap_node {
	heap_node(int key, int from, int to): key(key), from(from), to(to) {}
	
	int key;
	int from;
	int to;
	int delta = 0;
	heap_node* left = nullptr;
	heap_node* right = nullptr;

	void mpush() {
		key += delta;
		
		if (left)
			left->delta += delta;
		if (right)
			right->delta += delta;

		delta = 0;
	}

	heap_node* pop() {
		mpush();
		return merge(left, right);
	}
};

heap_node* merge(heap_node* a, heap_node* b) {
	if (not a)
		return b;
	if (not b)
		return a;

	a->mpush(), b->mpush();
	if (not (a->key <= b->key))
		swap(a, b);

	a->right = merge(a->right, b);
	swap(a->left, a->right);

	return a;
}

struct edge_t {
	int to;
	int weight;
};

struct dsu_t {
	vector<int> par;
	
	dsu_t(int n): par(n) {
		std::iota(ALL(par), 0);
	}

	int get_par(int v) {
		return (v == par[v] ? v : (par[v] = get_par(par[v])));
	}

	int merge(int v, int u) {
		v = get_par(v);
		u = get_par(u);

		par[v] = u;
		return u;
	}
};

struct arborescence {
	int n;
	int root;
	dsu_t dsu;
	
	vector<heap_node*> heaps;
	int64_t ans = 0;
	vector<char> collapsed;
	
	vector<vector<pair<int, int>>> ans_candidates;
	int ans_clock = 0;
	
	arborescence(int n, const vector<vector<edge_t>>& graph, int r): n(n), root(r), dsu(n),
																	 heaps(n, nullptr),
																	 collapsed(n, false),
																	 ans_candidates(n) {
		for (int v = 0; v < n; ++v)
			for (auto e: graph[v])
				heaps[e.to] = merge(heaps[e.to], new heap_node(e.weight, v, e.to));

		for (int v = 0; v < n; ++v)
			if (v != root)
				normalize(v);
		
		collapsed[root] = 1;
		for (int v = 0; v < n; ++v)
			if (not collapsed[v])
				collapse(v);
	}

	void normalize(int v) {
		v = dsu.get_par(v);

		heaps[v]->mpush();
		int w = heaps[v]->key;
		heaps[v]->delta -= w;
		ans += w;
	}
	
	void collapse(int start) {
		vector<int> stck = {start};
		vector<pair<int, int>> edges;
		
		while (true) {
			int v = stck.back();
			assert(heaps[v]);
			int u = dsu.get_par(heaps[v]->from);
			edges.emplace_back(heaps[v]->from, heaps[v]->to);
			
			if (collapsed[u] == 1) {
				for (int vert: stck)
					collapsed[vert] = 1;

				// ANS
				for (auto [v, u]: edges)
					ans_candidates[v].emplace_back(ans_clock++, u);
				// ANS.fi
				
				break;
			} else if (not collapsed[u]) {
				stck.push_back(u);
				collapsed[u] = 2;
			} else {
				int merge_with = v;
				
				while (true) {
					int vert = stck.back();
					stck.pop_back();
					heaps[vert] = heaps[vert]->pop();

					// ANS
					auto [vv, uu] = edges.back();
					edges.pop_back();
					ans_candidates[vv].emplace_back(ans_clock++, uu);
					// ANS.fi
					
					if (dsu.get_par(vert) != dsu.get_par(merge_with)) {
						int A = dsu.get_par(vert);
						int B = dsu.get_par(merge_with);
						
						heaps[dsu.merge(A, B)] = merge(heaps[A], heaps[B]);
					}
					
					if (vert == u)
						break;
				}

				u = dsu.get_par(u);
				stck.push_back(u);
				normalize(u);
			}
		}
	}

	vector<vector<int>> get_tree() {
		vector<vector<int>> tree(n);
		vector<char> used(n, false);
		
		map<pair<int, int>, int> qu;
		qu[make_pair(-1, root)] = -1;

		while (not qu.empty()) {
			int v = qu.begin()->first.second;
			int from = qu.begin()->second;
			qu.erase(qu.begin());
			if (used[v])
				continue;
			used[v] = 1;

			if (v != root)
				tree[from].push_back(v);
			
			for (auto u: ans_candidates[v])
				if (not used[u.second])
					qu[u] = v;
		}

		return tree;
	}
};
