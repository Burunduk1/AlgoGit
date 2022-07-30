struct edge_t { int a, b, w, i; };

struct node_t {
	edge_t e; // data
	int add;
	int x() { return e.w + add; }
	node_t *l, *r;
};
using pnode = node_t*;

pnode skewMerge(pnode a, pnode b) {
	if (!a || !b) return !a ? b : a;
	if (a->x() > b->x()) swap(a, b);
	b->add -= a->add, a->r = skewMerge(a->r, b);
	swap(a->l, a->r);
	return a;
}
void skewAdd(pnode &v, edge_t e) {
	v = skewMerge(v, new node_t {e, 0, 0, 0}); 
}
void skewExtractMin(pnode &a) {
	auto x = a->add; a = skewMerge(a->l, a->r), a->add += x; 
}

struct Solver {
	int n0, vn; // n initial vertexes + (n-1) cycles	
	vector<pnode> g; // g[v] = skew heap of adjacent edges
	vector<edge_t> parent; // current tree 
	int64_t sum_w;
	Solver(int n) : n0(n), vn(2 * n - 1), g(vn), parent(vn), sum_w(0) { }

	void addEdge(int a, int b, int w, int i) {
		skewAdd(g[b], {a, b, w, i});
	}
	void run() {
		vector<int> p(vn), p0; // p=DSU, p0=DSU without path-compression
		iota(all(p), 0), p0 = p;
		function<int(int)> get = [&](int i) {
			return i == p[i] ? i : (p[i] = get(p[i]));
		};
		auto next = [&](int b) { 
			return get(parent[b].a); 
		}; // b -> a

		auto select = [&](int v) {
			while (get(g[v]->e.a) == get(v)) 
				skewExtractMin(g[v]);
			assert(g[v]);
			parent[v] = g[v]->e;
			sum_w += g[v]->x();
			g[v]->add = -g[v]->e.w;
		};

		int cc = 1, n = n0;
		vector<int> used(vn, 0);
		vector<vector<pair<edge_t, int>>> cycle(vn);
		function<void(int)> goToRoot = [&](int v) {
			while (!used[v]) 
				select(v), used[v] = cc, v = next(v);
			if (used[v] != cc)
				return; 
			int id = n++;
			assert(id < vn);
			g[id] = g[v], p0[v] = p[v] = id;
			cycle[id] = {{parent[v], v}};
			for (int j = next(v); j != id; j = next(j)) {
				p0[j] = p[j] = id, g[id] = skewMerge(g[id], g[j]);
				cycle[id].push_back({parent[j], j});
			}
			goToRoot(id);
		};

		// calculate weight of the answer
		used[0] = cc; // root=0
		forn(i, n0)
			cc++, goToRoot(i);

		// recover answer 
		for (int i = n - 1; i >= n0; i--) {
			int v = parent[i].b; // edge comes into this vertex of the cycle[i]
			while (p0[v] != i) // this may cause Theta(n^2) in the worst case, but we may use LA in O(1) here
				v = p0[v]; 
			for (auto [e, j] : cycle[i])
				parent[j] = (j != v ? e : parent[i]);
		}
	}
};
