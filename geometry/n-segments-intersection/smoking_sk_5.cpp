#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define X first
#define Y second

const int maxn = 2e5;

int n, curx, evn = 0;
pair<int, int> p1[maxn], p2[maxn];
double Inv[maxn], Sum[maxn];

struct event {
	int x, i, f;
} ev[maxn * 2];

void Try(int i, int j) {
	if (!(min(p1[i].X, p2[i].X) <= max(p1[j].X, p2[j].X) && min(p1[j].X, p2[j].X) <= max(p1[i].X, p2[i].X) &&
		  min(p1[i].Y, p2[i].Y) <= max(p1[j].Y, p2[j].Y) && min(p1[j].Y, p2[j].Y) <= max(p1[i].Y, p2[i].Y))) 
		return;
	forn(_, 2) {
		int s1 = (p1[j].X - p1[i].X) * (p2[i].Y - p1[i].Y) - (p1[j].Y - p1[i].Y) * (p2[i].X - p1[i].X);
		int s2 = (p2[j].X - p1[i].X) * (p2[i].Y - p1[i].Y) - (p2[j].Y - p1[i].Y) * (p2[i].X - p1[i].X);
		if ((s1 > 0 && s2 > 0) || (s1 < 0 && s2 < 0))
			return;
		swap(i, j);
	}
	printf("YES\n%d %d\n", i + 1, j + 1);
	exit(0);
}

struct Less {
	bool operator() (int i, int j) const {
		if (i != j) Try(i, j);
		return Sum[i] - Sum[j] + curx * (Inv[i] - Inv[j]) < 0;
	}
};

int main() {
	scanf("%d", &n);
	forn(i, n)	{
		scanf("%d%d%d%d", &p1[i].X, &p1[i].Y, &p2[i].X, &p2[i].Y);
		if (p1[i] > p2[i])
			swap(p1[i], p2[i]);
		Inv[i] = (p2[i].X != p1[i].X) ? (double)(p2[i].Y - p1[i].Y) / (p2[i].X - p1[i].X) : 0;
		Sum[i] = p1[i].Y - Inv[i] * p1[i].X;
		ev[evn++] = {p1[i].X, i, 0};
		ev[evn++] = {p2[i].X, i, 1};
	}
	sort(ev, ev + evn, [](event a, event b) {
		return a.x < b.x || (a.x == b.x && a.f < b.f);
	});

	set<int, Less> s;
	forn(i, evn) {
		curx = ev[i].x; // need for "Less"
		if (!ev[i].f)
			s.insert(ev[i].i);
		else
			s.erase(ev[i].i);
	}
	puts("NO");
}
