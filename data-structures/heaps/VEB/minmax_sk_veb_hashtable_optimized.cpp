/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 1e8

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int K = 32, minK = 4;

typedef unsigned long long ull; // hash type
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

template <const int max_size, class HashType, class Data>
struct hashTable {
	HashType hash[max_size];
	Data f[max_size];
	int size;

	int position( HashType H ) const {
		int i = H % max_size;
		while (hash[i] && hash[i] != H)
			if (++i == max_size)
				i = 0;
		return i;
	}
	int addNew( HashType H ) {
		int i = H % max_size;
		while (hash[i] && hash[i] != -1)
			if (++i == max_size)
				i = 0;
		size++, hash[i] = H, f[i] = 0;
		return i;
	}
	bool count( HashType H ) const { return hash[position(H)] == H; }

	Data & operator [] ( HashType H ) {
		return f[position(H)];
	}
	void erase( HashType H ) { 
		int i = position(H);
		if (hash[i] == H)
			hash[i] = -1;
	}
};
hashTable<int(2e5 + 3), ull, Node*> table;

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
	union {
		Node* nonEmpty;
		int* cnt;
	};
	ull hash(T x) 					{ return (ull)(this - (Node *)0) * 17239U + (ull)x * 239017U; }
	Node* &inner( T x ) 			{ return table[hash(x)]; }
	void innerErase(int x, int K) 	{ table.erase(hash(x >> (K / 2))); }

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

		ull h = hash(i);
		int pos = table.position(h);
		if (table.hash[pos] != h) {
			pos = table.addNew(h);
			Add(nonEmpty, i, K);
		}
		Add(table.f[pos], z, K);
	}
	void delMin(int K) {
		if (K == minK) {
			for (cnt[min]--; !cnt[min]; min++)
				;
			return;
		}
		K /= 2;
		ull h = hash(min >> K);
		int pos = table.position(h);
		Node* &cell = table.f[pos];
		if (cell->size == 1) {
			table.hash[pos] = -1;
			DelMin(nonEmpty, K);
			int i = nonEmpty->min;
			min = pack(K, i, inner(i)->min);
		} else {
			DelMin(cell, K);
			min = pack(K, min >> K, cell->min);
		}
	}
	void delMax(int K) {
		if (K == minK) {
			for (cnt[max]--; !cnt[max]; max--)
				;
			return;
		}
		K /= 2;
		ull h = hash(max >> K);
		int pos = table.position(h);
		Node* &cell = table.f[pos];
		if (cell->size == 1) {
			table.hash[pos] = -1;
			DelMax(nonEmpty, K);
			int i = nonEmpty->max;
			max = pack(K, i, inner(i)->max);
		} else {
			DelMax(cell, K);
			max = pack(K, max >> K, cell->max);
		}
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
