/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

struct node {
	node *l, *r;
	int x;
};
using pnode = node*;
pnode merge(pnode a, pnode b) { // max count of usage : 3 414 759 on test 11
	if (!a || !b) return a ? a : b;
	if (a->x > b->x) swap(a, b);
	a->r = merge(a->r, b), swap(a->l, a->r);
	return a;
}
int main() {
	int n = readInt();
	node *h = 0;
	while (n--)
		h = merge(h, new node {0, 0, readInt()});
	for (; h; h = merge(h->l, h->r))
		writeInt(h->x, ' ');
}
