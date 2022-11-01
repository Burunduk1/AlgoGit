/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <algorithm>

struct node {
	int w, data, add;
	int x() { return w + add; }
	node *l, *r;
};
using pnode = node*;

pnode Merge(pnode a, pnode b) {
	if (!a || !b) return !a ? b : a;
	if (a->x() > b->x()) std::swap(a, b);
	b->add -= a->add, a->r = Merge(a->r, b);
	std::swap(a->l, a->r);
	return a;
}
void ExtractMin(pnode &root) {
	int d = root->add;
	root = Merge(root->l, root->r), root->add += d;
}
void Add(pnode &root, int w, int data) {
	root = Merge(root, new node {w, data, 0, 0, 0});
}
void Increase(pnode &root, int delta) {
	root->add += delta;
}
