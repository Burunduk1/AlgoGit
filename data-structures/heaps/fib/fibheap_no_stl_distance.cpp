/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 1e8
#include "optimization.h" // http://acm.math.spbu.ru/~sk1/algo/lib/optimization.h.html
#include <climits>

using namespace std::rel_ops;
using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template <const int V, const int E>
struct MultiList {
	int e, he[V], ne[E + 1], to[E + 1], w[E + 1];
	MultiList() : e(1) { }
	void add(int v, int x, int y) {
		to[e] = x, ne[e] = he[v], w[e] = y, he[v] = e++;
	}
};

const int N = 5e3;
const int M = 1e5;

int n, d[N], p[N]; // distance, previous vertex
MultiList<N, 2 * M> c;

struct T {
	int x;
	bool operator < (const T &b) const { return d[x] < d[b.x]; }
};

struct FibHeap {
	struct Node;
	struct Node {
		T x;
		int marked, size;
		Node *p, *l, *r, *lc, *rc;
		Node(const T &x) : x(x), marked(0), size(0), p(0), l(0), r(0), lc(0), rc(0) { }
	};
	#define add_to(right, v) right->r = v, v->l = right, v->r = 0, right = v
	#define erase(L, R, v) if (R != v) v->l->r = v->r, v->r->l = v->l; else R = R->l, R->r = 0;

	Node *min, *l_root, *r_root;
	FibHeap() : min(0), l_root(new Node(T())), r_root(l_root) { }
	
	void relax(Node *v) {
		if (!min || min->x > v->x)
			min = v;
	}
	void newRoot(Node *v) {
		relax(v);
		add_to(r_root, v);
	} 
	Node *add(const T &x) {
		Node *v = new Node(x);
		Node *emptyList = new Node(x);
		v->lc = v->rc = emptyList;
		newRoot(v);
		return v;
	}
	void decreaseKey(Node *v) {
		do {
			v->marked = 0;
			if (!v->p) 
				return;
			Node *p = v->p;
			erase(p->lc, p->rc, v);
			p->size--;
			v->p = 0;
			newRoot(v);
			v = p;
		} while (v->p && v->marked++);
	}
	Node *join(Node *a, Node *b) {
		if (a->x > b->x)
			swap(a, b);
		add_to(a->rc, b), a->size++;
		b->p = a;
		return a;
	}
	T extractMin() {
		static Node *node[100];
		static vector<int> ranks;
		assert(!empty());
		T res = min->x;
		erase(l_root, r_root, min);
		for (Node *v = min->lc->r; v; v = v->r)
			v->p = 0;
		r_root->r = min->lc->r;
		int rank;
		for (Node *v = l_root->r, *next; v; v = next) {
		    next = v->r;
			while (node[rank = v->size])
				v = join(v, node[rank]), node[rank] = 0;
			node[rank] = v;
			ranks.push_back(rank); 
		}
		r_root = l_root; 
		min = 0;
		for (int rank : ranks)
			if (node[rank])
				newRoot(node[rank]), node[rank] = 0;
		ranks.clear();
		return res;
	}
	bool empty() {
		return !min;
	}
};

FibHeap h; // compare using d
FibHeap::Node* node[N];

void change(int v, int D, int P) {
	d[v] = D, p[v] = P;
	if (!node[v])
		node[v] = h.add(T {v});
	else
		h.decreaseKey(node[v]);
}

void Dijkstra(int v) { // c[], v -> d
	fill(d, d + n, INT_MAX);
	fill(node, node + n, (FibHeap::Node *)0);
	change(v, 0, -1);
	while (!h.empty()) {
		int tmp, x, v = h.extractMin().x;
		for (int e = c.he[v]; e; e = c.ne[e])
			if (d[x = c.to[e]] > (tmp = d[v] + c.w[e]))
				change(x, tmp, v);
	}
}

int main() {
	n = readInt();
	int m = readInt();
	int s = readInt() - 1;
	int t = readInt() - 1;
	forn(i, m) {
		int a = readInt() - 1;
		int b = readInt() - 1;
		int w = readInt();
		c.add(a, b, w);
		c.add(b, a, w);
	}
	Dijkstra(t);
	if (d[s] == INT_MAX)
		writeInt(-1, '\n');
	else {
		writeInt(d[s], '\n');
		while (s != -1)
			writeInt(s + 1, ' '), s = p[s];
	}
}
