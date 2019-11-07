// release version: asserts should be off

#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

template<class T>
struct List {
    vector<T> data;
    vector<int> head, next;
    int n;
    List(int N, int SIZE) : data(SIZE), head(N, -1), next(SIZE), n(0) { }
    void add(int i, T x) {
        assert(0 <= i && i < (int)head.size() && n < (int)data.size());
        next[n] = head[i], data[n] = x, head[i] = n++;
    }
};
// List<int> g(n, m);

void dfs(int v, const List<int> &g) {
    for (int i = g.head[v]; i != -1; i = g.next[i]) {
        auto x = g.data[i];
        printf("%d ---> %d\n", v, x);
        dfs(x, g);
    }
}

/** Example of usage */
int main() {
    int n;
    assert(scanf("%d", &n) == 1);
    List<int> g(n, n - 1);
    for (int i = 1; i < n; i++) {
        int p; // parent
        assert(scanf("%d", &p) == 1), p--;
        g.add(p, i);
    }
    dfs(0, g);
}
