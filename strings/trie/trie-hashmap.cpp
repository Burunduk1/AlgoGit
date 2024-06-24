#include <vector>

using namespace std;

// ['a'..'a'+ALPHA)
template <const int maxV, const int ALPHA>
struct Trie { // 
	struct Vertex {
		int next[ALPHA], is_end;
	};
	vector<Vertex> t;
	int root = 0, n = 1;

	Trie() : t(maxV+1) { }

	bool add(const char *l, const char *r) { // [l,r)
		int v = root;
		for (; l != r; l++) {
			int &u = t[v].next[*l - 'a'];
			if (!u)
				u = n++;
			v = u;
		}
		return t[v].is_end++;
	}
	bool find(const char *l, const char *r) { // [l,r)
		int v = root;
		for (; l != r; l++) {
			const int &u = t[v].next[*l - 'a'];
			if (!u)
				return 0;
			v = u;
		}
		return 1;
	}
	void del(const char *l, const char *r) { // [l,r)
		int v = root;
		for (; l != r; l++)
			v = t[v].next[*l - 'a'];
		t[v].is_end = 0;
	}
};
Trie<100*30, 2> t; // for 100 strings of length 30, for alphabet "ab"
