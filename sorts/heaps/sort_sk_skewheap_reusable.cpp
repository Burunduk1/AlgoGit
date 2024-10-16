struct node {
	node *l, *r;
	int x;
};
using pnode = node*;

pnode mergeHeaps(pnode a, pnode b) {
	if (!a || !b) return a ? a : b;
	if (a->x > b->x) swap(a, b);
	a->r = mergeHeaps(a->r, b), swap(a->l, a->r);
	return a;
}
void heapSort(vector<int> &a) {
	node *h = 0;
	for (int &x : a) h = mergeHeaps(h, new node {0, 0, x});
	for (int &x : a) x = h->x, h = mergeHeaps(h->l, h->r);
}

