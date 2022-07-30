/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 *
 * Условие:
 *		Дано множество слов: 50 слов по 10 символов
 *		Построить бор минимального размера, содержащий все данные слова, как подстроки. *
 * 
 * Решение:
 * 		1. Удалить все s, являющиеся чьими-то подстроками.
 *		2. Для каждой пары i, j найти w(i,j) --- вес вставки j, как ответвления от i.
 *		3. Запустить алгоритм двух китайцев поиска ориентированного MST на матрице весов w.
 */

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()
#define pb push_back 
#define all(a) (a).begin(), (a).end()

typedef vector <int> vi;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;
	vector<string> s(n);
	forn(i, n) cin >> s[i];
	forn(i, n) forn(j, n) if (i != j && s[i].find(s[j]) != string::npos) {
		s.erase(s.begin() + j);
		n--, i = 0, j = -1;
	}
	
	vector<vi> c(n, vi(n));
	vector<vi> pos(n, vi(n));
	forn(i, n)               
		forn(j, n) {
			c[i][j] = -1;
			for (int t = 0; t < sz(s[i]); t++) {
				int lcp = 0;
				while (t + lcp < sz(s[i]) && s[i][t + lcp] == s[j][lcp])
					lcp++;
				if (lcp > c[i][j])
					c[i][j] = lcp, pos[i][j] = t;
			}
		}

	#include "d-2chinese.cpp"		
		
	int vn = 1, len = 1;
	forn(i, n) {
		len += sz(s[i]);
		if (res[i] != -1)
			len -= c[res[i]][i];
	}
	printf("%d\n", len);
	vector<int> used(n, 0), path[n];
	printf("0\n");
	function<void(int)> out = [&]( int v ) {
		if (v == -1 || used[v]) return;
		used[v] = 1;
		out(res[v]);
		auto &P = path[v];
		if (res[v] == -1) {
			P.pb(vn);
			for (char c : s[v])
				printf("%d %c\n", P.back(), c),	P.pb(++vn);
		} else {
			int u = res[v];
			forn(i, c[u][v] + 1)
				P.pb(path[u][pos[u][v] + i]);
			for (int i = c[u][v]; i < sz(s[v]); i++)
				printf("%d %c\n", P.back(), s[v][i]), P.pb(++vn);
		}			
	};
	forn(i, n)
		out(i);
}
