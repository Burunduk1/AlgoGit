/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 1e8

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int K = 32, minK = 4;

typedef unsigned T;

/** x = (i << K) + z */
void unpack(T x, int K, T &i, T &z) {
	i = x >> K;
	z = x & (((T)1 << K) - 1);
}
T pack(int K, T i, T z) {
	return (i << K) + z;
}

struct Node;
void Add(Node* &v, T x, int K);
void DelMin(Node* &v, int K);
void DelMax(Node* &v, int K);

/**
 * size=0 => Node* v=0
 * size=1 => min=max=x
 * size>1 => 
 *		C := 2^{K/2}
 *		K = minK => cnt[x]=count, x \in [0..2^K)
 *		K > minK =>	inner[i] = heap { x-i*C | x \in [i*C..(i+1)*C) }
 *					nonEmpty[i] = heap { x/C }
 */
struct Node {
	T size, min, max;
	unordered_map<T, Node*> inner;
	union {
		Node* nonEmpty;
		int* cnt;
	};

	Node(T x) {
		size = 1, min = max = x;
	}
	void init(int K) {
		if (K == minK)
			cnt = new int[1 << minK]();
		else
			nonEmpty = 0;
	}
	void add(T x, int K) {
		min = ::min(min, x);
		max = ::max(max, x);
		if (K == minK) {
			cnt[x]++;
			return;
		}
		T i, z;
		K /= 2;
		unpack(x, K, i, z);
		if (!inner.count(i))
			Add(nonEmpty, i, K);
		Add(inner[i], z, K);
	}
	void delMin(int K) {
		if (K == minK) {
			for (cnt[min]--; !cnt[min]; min++)
				;
			return;
		}
		K /= 2;
		Node* &cell = inner[min >> K];
		if (cell->size == 1) {
			inner.erase(min >> K);
			DelMin(nonEmpty, K);
		} else
			DelMin(cell, K);
		int i = nonEmpty->min, z = inner[i]->min;
		min = pack(K, i, z);
	}
	void delMax(int K) {
		if (K == minK) {
			for (cnt[max]--; !cnt[max]; max--)
				;
			return;
		}
		K /= 2;
		Node* &cell = inner[max >> K];
		if (cell->size == 1) {
			inner.erase(max >> K);
			DelMax(nonEmpty, K);
		} else {
			DelMax(cell, K);
		}
		int i = nonEmpty->max, z = inner[i]->max;
		max = pack(K, i, z);
	}
	void innerErase(int x, int K) {
		inner.erase(x >> (K / 2));
	}
};

void Add(Node* &v, T x, int K) {
	if (!v) {
		v = new Node(x);
		return;
	}
	if (v->size++ == 1) 
		v->init(K), v->add(v->min, K);
	v->add(x, K);
}

void DelMin(Node* &v, int K) {
	v->size--;
	if (v->size == 0)
		v = 0;
	else if (v->size == 1) {
		v->innerErase(v->min, K);
		v->innerErase(v->max, K);
		v->min = v->max;
	} else 
		v->delMin(K);
}

void DelMax(Node *&v, int K) {
	v->size--;
	if (v->size == 0)
		v = 0;
	else if (v->size == 1) {
		v->innerErase(v->min, K);
		v->innerErase(v->max, K);
		v->max = v->min;
	} else 
		v->delMax(K);
}

int main() {
	Node *root = 0; // VEB tree
	char s[99];
	readWord(s);
	while (!seekEof()) {
		int x;
		readWord(s);
		if (!strcmp(s, "GetMin")) {
			writeInt(root->min, '\n');
			DelMin(root, K);
		} else if (!strcmp(s, "GetMax")) {
			writeInt(root->max, '\n');
			DelMax(root, K);
		} else {
			sscanf(strchr(s, '(') + 1, "%d", &x);
			Add(root, x, K);
		}
	}
}
