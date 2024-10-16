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
	if (!b) return a;	
	if (a->x > b->x) swap(a, b);
	b->next = a->child, a->child = b;
	return a;
}
pnode pairing(pnode h) {
	return !h ? 0 : meld(h, pairing(h->next)); // TL: linear depth as result
}
int main() {
	int n = readInt();
	node *h = 0;
	while (n--)
		h = new node {h, 0, readInt()}; // add
	for (; h; h = h->child) // h=child : extract min
		h = pairing(h), writeInt(h->x, ' ');
}
