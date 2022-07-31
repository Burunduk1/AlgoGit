struct node_t {
	int w, i; // data
	int add;
	int x() { return w + add; }
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
void skewAdd(pnode &v, int w, int i) {
	v = skewMerge(v, new node_t {w, i, 0, 0, 0}); 
}
void skewExtractMin(pnode &a) {
	auto x = a->add; a = skewMerge(a->l, a->r), a->add += x; 
}

struct Solver {
	int n, m;
	vector<pnode> g; // g[v] = skew heap of adjacent edges
	struct edge_t { int a, b; };
	vector<edge_t> e;
	vector<vector<int>> es; 
	vector<int> ans; // set of indexes of answer-tree
	int64_t sum_w;
	Solver(int n) : n(n), m(0), g(n), es(n), sum_w(0) { }

	void addEdge(int a, int b, int w) {
		int i = m++;
		skewAdd(g[b], w, i);
		e.push_back({a, b});
		es[a].push_back(i); // to recover the answer
	}
	void run() {
		vector<int> p(n), need(m, -1), parent(n); // p=DSU, need=edge priority, parent=current tree
		iota(all(p), 0);
		function<int(int)> get = [&](int i) {
			return i == p[i] ? i : (p[i] = get(p[i]));
		};
		auto next = [&](int i) { 
			return get(e[parent[i]].a); // b -> a
		}; 

		auto select = [&](int v) {
			while (get(e[g[v]->i].a) == get(v)) 
				skewExtractMin(g[v]);
			assert(g[v]);
			need[g[v]->i] = n + 1; // maximum (if is edge of tree)
			parent[v] = g[v]->i;
			sum_w += g[v]->x();
			g[v]->add = -g[v]->w;
		};

		int cc = 1, cycleCnt = 0;
		vector<int> used(n, 0);
		function<void(int)> goToRoot = [&](int v) {
			while (!used[v]) 
				select(v), used[v] = cc, v = next(v);
			if (used[v] != cc)
				return; 
			need[parent[v]] = ++cycleCnt;
			for (int j = next(v); j != v; j = next(j)) {
				need[parent[j]] = cycleCnt;
				p[j] = v, g[v] = skewMerge(g[v], g[j]);
			}
			used[v] = 0, goToRoot(v);
		};

		// calculate weight of the answer
		used[0] = cc; // root=0
		forn(i, n)
			cc++, goToRoot(i);

		// recover answer 
		int v = 0, i = -1; // v=root=0
		cc++;
		priority_queue<pair<int, int>> q;
		forn(_, n - 1) {
			used[v] = cc;
			for (auto i : es[v]) 
				if (need[i] != -1)
					q.push({-need[i], i});
			while (used[v] == cc)
				i = q.top().second, q.pop(), v = e[i].b;
			ans.push_back(i);
		}
	}
};
