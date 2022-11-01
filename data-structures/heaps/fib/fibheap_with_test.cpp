#include <bits/stdc++.h>

using namespace std;

struct FibHeap {
	struct Node {
		int x, marked, deleted;
		list<Node*>::iterator pos;
		Node *parent;
		list<Node*> children;
		Node(int x) : x(x), marked(0), deleted(0), parent(0) { }
	};

	list<Node*> roots;
	Node *min;
	FibHeap() : min(0) { }
	
	static void add(list<Node*> &l, Node *v) {
		v->pos = l.insert(l.end(), v);
	}
	void relax(Node *v) {
		if (!min || min->x > v->x)
			min = v;
	}
	void newRoot(Node *v) {
		add(roots, v), relax(v);
	} 
	Node *add(int x) {
		Node *v = new Node(x);
		newRoot(v);
		return v;
	}
	void merge(FibHeap &h) {
		roots.splice(roots.end(), h.roots);
		relax(h.min);
	}
	void decreaseKey(Node *v, int newX) {
		v->x = newX;
		do {
			v->marked = 0;
			if (!v->parent) 
				return;
			Node *p = v->parent;
			p->children.erase(v->pos);
			v->parent = 0;
			newRoot(v);
			v = p;
		} while (v->parent && v->marked++);
	}
	Node *join(Node *a, Node *b) {
		if (a->x > b->x)
			swap(a, b);
		add(a->children, b), b->parent = a;
		return a;
	}
	int extractMin() {
		static Node *node[100];
		static vector<int> ranks;
		assert(!empty());
		int res = min->x, rank;
		min->deleted = 1; // if we have external links to the heap, it may be useful
		roots.erase(min->pos);
		for (auto v : min->children)
			v->parent = 0;
		roots.splice(roots.end(), min->children);
		for (Node *v : roots) {
			while (node[rank = v->children.size()]) 
				v = join(v, node[rank]), node[rank] = 0;
			node[rank] = v;
			ranks.push_back(rank); 
		}
		roots.clear(), min = 0;
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

/** Test area */

void stamp(const char *s) {
	printf("%.2f : %s\n", 1. * clock() / CLOCKS_PER_SEC, s);
}

const int N = 100000;
int a[N];
FibHeap::Node *b[N];

int main() {
	FibHeap<int> f;
	for (int i = 0; i < N; i++) {
		a[i] = rand();
	}
	stamp("inited");
	for (int i = 0; i < N; i++) {
		b[i] = f.add(a[i]);
	}
	stamp("added");
	for (int i = 0; i < N / 2; i++) {
		int x = f.extractMin();
	}	
	stamp("extracted [N/2]");
	for (int j = 0; j < N; j++) {
		if (!b[j]->deleted) {
			int value = min(rand(), rand());
			if (value < b[j]->x) {
				f.decreaseKey(b[j], value);
			}
		}
	}
	stamp("decreased [N/2]");
	for (int i = 0; i < N / 2; i++) {
		int x = f.extractMin();
	}	
	stamp("extracted [N/2]");
	assert(f.empty());
}
