// Владимир Яковлев, https://acm.timus.ru/problem.aspx?space=1&num=1469

#include <bits/stdc++.h>

using namespace std;

const int MAX = 2e5;

struct pnt {
	int x, y, segIndex;
	bool left;

	void Read()	{
		scanf("%d %d", &x, &y);
	}
	bool operator < (const pnt& p) const {
		return x < p.x || (x == p.x && (y < p.y || (y == p.y && left && !p.left)));
	}
	pnt operator - (const pnt& p) const {
		return {x - p.x, y - p.y, -1, 0};
	}
};

int Cross(const pnt& u, const pnt& v) {
	int cr = u.x * v.y - u.y * v.x;
	return cr < 0 ? -1 : (cr > 0 ? 1 : 0);
}

int n;
struct Segment {
	pnt a, b, vec;
} s[MAX];
pnt p[MAX*2];

void Read() {
	scanf("%d", &n);
	for (int i=0; i<n; i++)	{
		s[i].a.Read();
		s[i].b.Read();
		if (s[i].b < s[i].a) swap(s[i].a, s[i].b);
		s[i].a.segIndex = i, s[i].a.left = true;
		s[i].b.segIndex = i, s[i].b.left = false;
		s[i].vec = s[i].b - s[i].a;
		p[i*2] = s[i].a;
		p[i*2+1] = s[i].b;
	}
}

struct Less {
	bool operator () (int i, int j) const {
		if (i == j) return false;
		auto si = s[i], sj = s[j];
		int cr1 = Cross(si.vec, sj.a - si.a);
		int cr2 = Cross(si.vec, sj.b - si.a);
		int cr3 = Cross(sj.vec, si.a - sj.a);
		int cr4 = Cross(sj.vec, si.b - sj.a);
		if (cr1 * cr2 <= 0 && cr3 * cr4 <= 0) {
			printf("YES\n%d %d\n", i+1, j+1);
			exit(0);
		}
		return (cr1 > 0 && cr2 > 0) || (cr3 < 0 && cr4 < 0);
	}
};

void Solve() {
	stable_sort(p, p + 2*n);
	set<int, Less> q;
	for (auto e : p)
		if (e.left)
			q.insert(e.segIndex);
		else
			q.erase(e.segIndex);
	printf("NO\n");
}

int main() {
	Read();
	Solve();
}
