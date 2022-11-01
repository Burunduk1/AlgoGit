/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

struct QuakeHeap {
	struct node;
	using pnode = node*;

	struct node {
		int k, x;
		pnode l, r;
		node(int x) : k(0), x(x), l(0), r(0) {}
		node(pnode l, pnode r) : k(l->k+1), x(min(l->x, r->x)), l(l), r(r) { }
	};

	vector<pnode> roots; // use list:roots & iterator:min_pos to do merge/meld in O(1)
	int min_pos = 0;

	int getMin() {
		return roots[min_pos]->x;
	}
	void add(pnode p) {
		roots.push_back(p);
		if (roots.back()->x < roots[min_pos]->x)
			min_pos = roots.size() - 1;
	}
	int extractMin() {
		int min = getMin();
		pnode p = roots[min_pos];
		swap(roots[min_pos], roots.back()), roots.pop_back();
		while (p->k > 0) {
			if (p->l->x != p->x)
				swap(p->l, p->r);
			roots.push_back(p->r), p = p->l;
		}
		unordered_map<int, pnode> m;
		for (auto p : roots) {
			while (m.count(p->k))
				p = new node(p, m[p->k]), m.erase(p->k - 1);
			m[p->k] = p;
		}
		roots.clear(), min_pos = 0;
		for (auto [k, p] : m)
			add(p);
		return min;
	}
	void add(int x) {
		add(new node(x));
	}
} h;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, x;
	char com;
	cin >> n;
	while (n-- && cin >> com) 
		if (com == '-')
			cout << h.extractMin() << "\n";
		else 
			cin >> x, h.add(x);
}
