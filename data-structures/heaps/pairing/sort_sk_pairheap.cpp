/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

struct node {
	node *next, *child;
	int x;
};
using pnode = node*;
pnode meld(pnode a, pnode b) { // max count of usage: 1 944 659 on test 7
	if (!a || !b) return a ? a : b;	
	if (a->x > b->x) swap(a, b);
	b->next = a->child, a->child = b;
	return a;
}
pnode pairing(pnode h) {
	if (!h) return 0;
	if (!h->next) return h;
	return meld(meld(h, h->next), pairing(h->next->next));
}
int main() {
	int n = readInt();
	node *h = 0;
	while (n--)
		h = new node {h, 0, readInt()}; // add
	for (; h; h = h->child) // h=child : extract min
		h = pairing(h), writeInt(h->x, ' ');
}
