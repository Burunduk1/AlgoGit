// Segment Tree

#define vmerge(a, b) ((a) + (b))
#define dmerge(a, b) ((a) + (b))
#define distr(a, b, n) ((a) + (b) * (n))
#define viden 0
#define diden 0

#define left(i) ((i) * 2 + 1)
#define right(i) ((i) * 2 + 2)

const int MAXN = 1000000;

int v[MAXN * 4];
int d[MAXN * 4];
int A[MAXN];

void down(int i, int l, int r) {
	v[left(i)] = distr(v[left(i)], d[i], l);
	d[left(i)] = dmerge(d[left(i)], d[i]);
	v[right(i)] = distr(v[right(i)], d[i], r);
	d[right(i)] = dmerge(d[right(i)], d[i]);
	d[i] = diden;
}

void update(int i, int l, int r, int a, int b, int p) {
	if (l >= r || r <= a || b <= l)
		return;
	if (a <= l && r <= b) {
		v[i] = distr(v[i], p, r - l);
		d[i] = dmerge(d[i], p);
	} else {
		int m = (l + r) / 2;
		down(i, m - l, r - m);
		update(left(i), l, m, a, b, p);
		update(right(i), m, r, a, b, p);
		v[i] = vmerge(v[left(i)], v[right(i)]);
	}
}

int get(int i, int l, int r, int a, int b) {
	if (l >= r || r <= a || b <= l)
		return viden;
	if (a <= l && r <= b) {
		return v[i];
	} else {
		int m = (l + r) / 2;
		down(i, m - l, r - m);
		return vmerge(get(left(i), l, m, a, b), get(right(i), m, r, a, b));
	}
}

void build(int i, int l, int r) {
	if (r - l == 1)
		v[i] = A[l];
	else {
		int m = (l + r) / 2;
		build(left(i), l, m);
		build(right(i), m, r);
		v[i] = vmerge(v[left(i)], v[right(i)]);
	}
}

// Fenwick Tree

const int MAXN = 1000000;

int F[MAXN];

int get(int i) {
	int ans = 0;
	for (; i >= 0; ans += F[i], i = (i & i + 1) - 1);
	return ans;
}

void add(int i, int v) {
	for (; i < MAXN; F[i] += v, i |= i + 1);
}

// Fenwick Tree Range Update

const int MAXN = 1000000;

int FA[MAXN], FM[MAXN];

int get(int i) {
	int m = 0, a = 0;
	for (int j = i; j >= 0; m += FM[j], a += FA[j], j = (j & j + 1) - 1);
	return m * i + a;
}

void add(int i, int m, int a) {
	for (int j = i; j < MAXN; FM[j] += m, FA[j] += a, j |= j + 1);
}

void add(int l, int r, int v) {
	add(l, v, -v * l);
	add(r, -v, v * r);
}

// Fenwick Tree Range Update 2D

const uigr MAXN = 1000;

lng F[MAXN][MAXN][4];

lng get(igr i, igr j) {
	lng a = 0;
	for (igr x = i; x >= 0; x = (x & x + 1) - 1)
		for (igr y = j; y >= 0; y = (y & y + 1) - 1)
			a += F[x][y][0] + F[x][y][1] * (i + 1) + F[x][y][2] * (j + 1) +
					F[x][y][3] * (i + 1) * (j + 1);
	return a;
}

void add(igr i, igr j, lng v) {
	for (igr x = i; x < MAXN; x |= x + 1)
		for (igr y = j; y < MAXN; y |= y + 1)
			F[x][y][0] += v * i * j,
			F[x][y][1] += -v * j,
			F[x][y][2] += -v * i,
			F[x][y][3] += v;
}

lng get(igr xl, igr xr, igr yl, igr yr) {
	--xl, --yl;
	return get(xr, yr) - get(xl, yr) - get(xr, yl) + get(xl, yl);
}

void add(igr xl, igr xr, igr yl, igr yr, lng v) {
	++xr, ++yr;
	add(xr, yr, v);
	add(xr, yl, -v);
	add(xl, yr, -v);
	add(xl, yl, v);
}

// Cartesian Tree

struct rand {
	ulng seed;
	rand(ulng seed = 0) : seed(seed) {}
	uigr operator()() {
		return (seed = seed * 6364136223846793005ll +
				1442695040888963407ll) >> 32;
	}
	uigr bool_rand(uigr a, uigr b) {
		return operator()() % (a + b) < a;
	}
} rndm;

struct ct {
	uigr l, r;
	uigr n;
	uigr x;
	ct(igr x = 0) : l(0), r(0), n(1), x(x) {}
};

const uigr MAXN = 15000000;

uigr buffer_size = 1;
ct buffer[MAXN];

uigr create(ct a) {
	buffer[buffer_size++] = a;
	return buffer_size - 1;
}

uigr size(uigr a) {
	return a == 0 ? 0 : buffer[a].n;
}

void recalc_down(uigr a) {}
void recalc_up(uigr a) {
	buffer[a].n = size(buffer[a].l) + size(buffer[a].r) + 1;
}

template<uigr PERSISTENT = 0>
uigr merge(uigr a, uigr b) {

	if (a == 0)
		return b;
	if (b == 0)
		return a;
	
	if (PERSISTENT == 1) {
		a = create(ct(buffer[a]));
		b = create(ct(buffer[b]));
	}
		
	recalc_down(a);
	recalc_down(b);
	
	if (rndm.bool_rand(buffer[b].n, buffer[a].n)) {
		buffer[b].l = merge<PERSISTENT>(a, buffer[b].l);
		recalc_up(b);
		return b;
	} else {
		buffer[a].r = merge<PERSISTENT>(buffer[a].r, b);
		recalc_up(a);
		return a;
	}
}

template<bln MIDDLE_L = 0, uigr PERSISTENT = 0>
std::pair<uigr, uigr> split(uigr a, igr x) {

	if (a == 0)
		return std::pair<uigr, uigr>(0, 0);
		
	if (PERSISTENT == 1)
		a = create(ct(buffer[a]));
	
	recalc_down(a);
	
	if (!MIDDLE_L && buffer[a].x < x || MIDDLE_L && !(x < buffer[a].x)) {
		std::pair<uigr, uigr> p = split<MIDDLE_L, PERSISTENT>(buffer[a].r, x);
		buffer[a].r = p.first;
		recalc_up(a);
		return std::pair<uigr, uigr>(a, p.second);
	} else {
		std::pair<uigr, uigr> p = split<MIDDLE_L, PERSISTENT>(buffer[a].l, x);
		buffer[a].l = p.second;
		recalc_up(a);
		return std::pair<uigr, uigr>(p.first, a);
	}
}

template<bln MIDDLE_L = 0, uigr PERSISTENT = 0>
std::pair<uigr, uigr> split_id(uigr a, uigr x) {

	if (a == 0)
		return std::pair<uigr, uigr>(0, 0);
		
	if (PERSISTENT == 1)
		a = create(ct(buffer[a]));
	
	recalc_down(a);
	
	if (!MIDDLE_L && size(buffer[a].l) < x || MIDDLE_L && !(x < size(buffer[a].l))) {
		std::pair<uigr, uigr> p = split_id<MIDDLE_L, PERSISTENT>(buffer[a].r,
				x - size(buffer[a].l) - 1);
		buffer[a].r = p.first;
		recalc_up(a);
		return std::pair<uigr, uigr>(a, p.second);
	} else {
		std::pair<uigr, uigr> p = split_id<MIDDLE_L, PERSISTENT>(buffer[a].l, x);
		buffer[a].l = p.second;
		recalc_up(a);
		return std::pair<uigr, uigr>(p.first, a);
	}
}

void debug(uigr a, uigr depth = 0) {
	for (uigr i = 0; i < depth; ++i)
		std::cout << "  ";
	if (a == 0) {
		std::cout << "NULL\n";
		return;
	}
	std::cout << "val: " << buffer[a].x << " size: " << buffer[a].n << "\n";
	debug(buffer[a].r, depth + 1);
	debug(buffer[a].l, depth + 1);
}

// Ford Falkerson With Scalability

igr dfs(uigr v, igr k) {
	used[v] = used_cur;
	if (v == t)
		return k;
	for (uigr i = 0; i < n; ++i)
		if (C[v][i] - F[v][i] > 0 && used[i] != used_cur) {
			igr mn = dfs(i, std::min(k, C[v][i] - F[v][i]));
			if (mn > 0) {
				F[v][i] += mn;
				F[i][v] -= mn;
				return mn;
			}
		}
	return 0;
}

//for (igr i = IGR_MAX; i; i >>= 1)
//	for (uigr tmp; ++used_cur, ans += tmp = dfs(s, i), tmp; );

// Linear Congruential Generator

ull rndms = 0;
uint rndm() { return (rndms = rndms * 6364136223846793005ll + 1442695040888963407ll) >> 32; }

// Prefix Function

const int MAXN = 1000000;

char a[MAXN];
int p[MAXN];

void prefix(int n) {
	p[0] = 0;
	for (int i = 1, k = 0; i < n; ++i) {
		while (k > 0 && a[i] != a[k])
			k = p[k - 1];
		if (a[i] == a[k])
			++k;
		p[i] = k;
	}
}

// Knuth Morris Pratt

#define substring(i) (cout << (i) << "\n")

const int MAXN = 1000000;

char b[MAXN];
char a[MAXN];
int p[MAXN];

void kmp(int n, int m) {
	for (int i = 0, k = 0; i < m; ++i) {
		while (k > 0 && b[i] != a[k])
			k = p[k - 1];
		if (b[i] == a[k])
			++k;
		if (k == n) {
			substring(i - n + 1);
			k = p[k - 1];
		}
	}
}

// Next And Previous Power Of Two

int pp2(int n) {
	int ans = 0;
	while ((n >>= 1) > 0)
		++ans;
	return ans;
}

int np2(int n) {
	int ans = 0;
	--n;
	while (n > 0)
		++ans, n >>= 1;
	return ans;
}

// Sparse Table

#define vmerge(a, b) (min((a), (b)))

const int MAXN = 1000000;
const int MAXH = 32;

int S[MAXH][MAXN];
int A[MAXN];

int get(int l, int r) {
	int i = pp2(r - l);
	return vmerge(S[i][l], S[i][r - (1 << i)]);
}

void build(int n) {
	for (int i = 0; i < n; ++i)
		S[0][i] = A[i];
	for (int i = 1; (1 << i) <= n; ++i)
		for (int j = 0; j <= n - (1 << i); ++j)
			S[i][j] = vmerge(S[i - 1][j], S[i - 1][j + (1 << (i - 1))]);
}

// LCA O(n log n), O(1)

const uigr MAXN = 100000, MAXH = 32;
std::pair<uigr, uigr> A[MAXH][MAXN * 2];
uigr A_size = 0, B[MAXN];
std::vector<uigr> g[MAXN];

void dfs(uigr v, uigr depth) {
	A[0][B[v] = A_size++] = std::make_pair(depth, v);
	for (uigr i = 0; i < g[v].size(); ++i)
		dfs(g[v][i], depth + 1),
		A[0][A_size++] = std::make_pair(depth, v);
}

uigr pp2(uigr n) {
	uigr ans = 0;
	while ((n >>= 1) > 0)
		++ans;
	return ans;
}

std::pair<uigr, uigr> get(uigr l, uigr r) {
	uigr i = pp2(r - l);
	return std::min(A[i][l], A[i][r - (1 << i)]);
}

void build(uigr n) {
	for (uigr i = 1; (1 << i) <= n; ++i)
		for (uigr j = 0; j <= n - (1 << i); ++j)
			A[i][j] = std::min(A[i - 1][j], A[i - 1][j + (1 << (i - 1))]);
}

// Cutedge, Cutvertex Finding

#define cutedge(a, b) (cout << (a) << " " << (b) << "\n")
#define cutvertex(a) (cout << (a) << "\n")

const int MAXN = 1000000;

vector<int> g[MAXN];
bool used[MAXN];
int tin[MAXN], fup[MAXN];
int timer = 0;

void dfs(int v, int p) {
	used[v] = true;
	fup[v] = tin[v] = timer++;
	int children = 0;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)
			continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				cutedge(v, to);
			if (fup[to] >= tin[v] && p != -1)
				cutvertex(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		cutvertex(v);
}

// Kuhn

#define edge(a, b) (cout << (a) << " " << (b) << "\n")

const int MAXN = 1000000;
const int MAXK = 1000000;

vector<int> g[MAXN];
int used[MAXN];
int mt[MAXK];
int iter = 0;

bool dfs(int v) {
	used[v] = iter;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || (used[mt[to]] != iter && dfs(mt[to]))) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

void kuhn(int n, int k) {
	memset(mt, -1, k * sizeof(int));
	memset(used, -1, n * sizeof(int));
	for (; iter < n; ++iter)
		dfs(iter);
	for (int i = 0; i < k; ++i)
		if (mt[i] != -1)
			edge(mt[i], i);
}

// Dijkstra

const int MAXN = 1000000;
const uint UINF = -1;

vector<pair<int, int> > g[MAXN];
uint d[MAXN];
int p[MAXN];

void dijkstra(int n, int s) {
	memset(d, UINF, n * sizeof(uint));
	d[s] = 0;
	p[s] = -1;
	set<pair<int, int> > q;
	q.insert(make_pair(0, s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (int i = 0; i < g[v].size(); ++i) {
			int to = g[v][i].first, len = g[v][i].second;
			if (d[v] + len < d[to]) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert(make_pair(d[to], to));
			}
		}
	}
}

// Prima

const int MAXN = 1000000;
const uint UINF = -1;

vector<pair<int, int> > g[MAXN];
uint d[MAXN];
int p[MAXN];

void prima(int n, int s) {
	memset(d, UINF, n * sizeof(uint));
	d[s] = 0;
	p[s] = -1;
	set<pair<int, int> > q;
	q.insert(make_pair(0, s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (int i = 0; i < g[v].size(); ++i) {
			int to = g[v][i].first, len = g[v][i].second;
			if (len < d[to]) {
				q.erase(make_pair(d[to], to));
				d[to] = len;
				p[to] = v;
				q.insert(make_pair(d[to], to));
			}
		}
	}
}

// Floyd

const int MAXN = 1000;

int g[MAXN][MAXN];
int d[MAXN][MAXN];
int p[MAXN][MAXN];

void Floyd(int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			p[i][j] = -1;
			d[i][j] = g[i][j];
		}
		d[i][i] = 0;
	}
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
}

void path(int i, int j) {
	int k = p[i][j];
	if (k == -1)
		return;
	path(i, k);
	cout << k << " ";
	path(k, j);
}

// Vector

struct vt {
	double x, y;
	vt() {}
	vt(double px, double py) : x(px), y(py) {}
	vt(const vt &v) : x(v.x), y(v.y) {}
	vt(vt a, vt b) : x(b.x - a.x), y(b.y - a.y) {}
	vt operator-() {			return vt(-x, -y);}
	vt operator+(vt v) {		return vt(x + v.x, y + v.y);}
	vt operator-(vt v) {		return vt(x - v.x, y - v.y);}
	vt operator*(vt v) {		return vt(x * v.x, y * v.y);}
	vt operator/(vt v) {		return vt(x / v.x, y / v.y);}
	vt operator*(double k) {	return vt(x * k, y * k);}
	vt operator/(double k) {	return vt(x / k, y / k);}
	double operator^(vt v) {	return x * v.x + y * v.y;}
	double operator%(vt v) {	return x * v.y - y * v.x;}
	double len2() {				return x * x + y * y;}
	double len() {				return sqrt(len2());}
	double dst2(vt v) {			return vt(*this, v).len2();}
	double dst(vt v) {			return sqrt(dst2(v));}
	vt norm() {					return *this / len();}
	vt rot90() {				return vt(-y, x);}
	vt rot270() {				return vt(-y, x);}
	vt rot(double c, double s) {return vt(c * x - s * y, s * x + c * y);}
	double ang() {				return atan2(y, x);}
	double ang(vt v) {			return atan2(*this % v, *this ^ v);}
};

// Line And Line

pair<vt, vt> lland(vt a, vt b, vt c, vt d) {
	double z = vt(a, b) % vt(c, d);
	double c1 = vt(a, c) % vt(c, d);
	double c2 = vt(a, c) % vt(a, b);
	if (ep(z) == 0)
		return ep(c1) == 0 ? make_pair(vt(NaN, NaN), vt(NaN, NaN)) : make_pair(vt(Inf, Inf), vt(Inf, Inf));
	vt u = vt(c1 / z, c2 / z);
	return make_pair(a + vt(a, b) * u.x, u);
}

// Point Tangent Circle

pair<vt, vt> pctan(vt p, vt o, double r) {
	double a = p.dst2(o);
	double b = a - r * r;
	vt c = vt(p, o) * b;
	if (ep(b) == 0)
		return make_pair(p + c / a, p + c / a);
	if (b < 0)
		return make_pair(vt(Inf, Inf), vt(Inf, Inf));
	vt d = vt(p, o).rot90() * sqrt(b) * r;
	return make_pair(p + (c + d) / a, p + (c - d) / a);
}

// Line And Circle

pair<vt, vt> lcand(vt p1, vt p2, vt o, double r) {
	double a = p1.dst(p2);
	double b = vt(o, p1) % vt(o, p2) / a;
	vt n = vt(p1, p2) / a;
	vt c = o - n.rot90() * b;
	double k = r * r - b * b;
	if (ep(k) == 0)
		return make_pair(c, c);
	if (k < 0)
		return make_pair(vt(Inf, Inf), vt(Inf, Inf));
	vt d = n * sqrt(k);
	return make_pair(c + d, c - d);
}

// Circle And Circle

pair<vt, vt> ccand(vt o1, double r1, vt o2, double r2) {
	double a = o1.dst(o2);
	if (ep(a) == 0)
		if (ep(r1) == r2)
			return make_pair(vt(NaN, NaN), vt(NaN, NaN));
		else
			return make_pair(vt(Inf, Inf), vt(Inf, Inf));
	double b = (r1 * r1 - r2 * r2 + a * a) / 2 / a;
	vt c = o1 + vt(o1, o2) / a * b;
	double k = r1 * r1 - b * b;
	if (ep(k) == 0)
		return make_pair(c, c);
	if (k < 0)
		return make_pair(vt(Inf, Inf), vt(Inf, Inf));
	vt d = vt(o1, o2).rot90() / a * sqrt(k);
	return make_pair(c + d, c - d);
}

// Unordered

pair<vt, vt> lland(vt a, vt b, vt c, vt d) {
	dbl z = vt(a, b) % vt(c, d);
	dbl c1 = vt(a, c) % vt(c, d);
	dbl c2 = vt(a, c) % vt(a, b);
	if (ep(z) == 0)
		return ep(c1) == 0 ? mp(VTNaN, VTNaN) : mp(VTInf, VTInf);
	vt u = vt(c1 / z, c2 / z);
	return mp(a + vt(a, b) * u.x, u);
}

pair<vt, vt> pctan(vt p, vt o, dbl r) {
	dbl a = p.dst2(o);
	dbl b = a - r * r;
	if (ep(b) == 0)
		return mp(p, p);
	if (b < 0)
		return mp(VTInf, VTInf);
	vt c = vt(p, o) * b;
	vt d = vt(p, o).rot90() * (sqrt(b) * r);
	return mp(p + (c + d) / a, p + (c - d) / a);
}

pair<vt, vt> lcand(vt p1, vt p2, vt o, dbl r) {
	dbl a = p1.dst(p2);
	dbl b = vt(o, p1) % vt(o, p2) / a;
	vt n = vt(p1, p2) / a;
	vt c = o - n.rot90() * b;
	dbl k = r * r - b * b;
	if (ep(k) == 0)
		return mp(c, c);
	if (k < 0)
		return mp(VTInf, VTInf);
	vt d = n * sqrt(k);
	return mp(c + d, c - d);
}

pair<vt, vt> ccand(vt o1, dbl r1, vt o2, dbl r2) {
	dbl a = o1.dst(o2);
	if (ep(a) == 0)
		return ep(r1) == r2 ? mp(VTNaN, VTNaN) : mp(VTInf, VTInf);
	dbl b = (r1 * r1 - r2 * r2 + a * a) / (a * 2);
	vt c = o1 + vt(o1, o2) * (b / a);
	dbl k = r1 * r1 - b * b;
	if (ep(k) == 0)
		return mp(c, c);
	if (k < 0)
		return mp(VTInf, VTInf);
	vt d = vt(o1, o2).rot90() * (sqrt(k) / a);
	return mp(c + d, c - d);
}

/**
 * Minkowski Addition.
 */
cvx operator+(cvx a, cvx b) {

	a.clean();
	a.sort_ang();
	b.clean();
	b.sort_ang();

	if (a.size() == 0 || b.size() == 0)
		return cvx();

	cvx c;

	uigr i = 0, j = 0;
	vt v1 = vt(a[i], a[(i + 1) % a.size()]);
	vt v2 = vt(b[j], b[(j + 1) % b.size()]);

	for (uigr k = a.size() + b.size(); k > 0; --k) {
		c.push(a[i % a.size()] + b[j % b.size()]);
		if (j == b.size() || (i != a.size() && v1.ls_ang(v2))) {
			++i;
			v1 = vt(a[i], a[(i + 1) % a.size()]);
		} else {
			++j;
			v2 = vt(b[j], b[(j + 1) % b.size()]);
		}
	}

	return c;
}

bln isempty(const darr<line> &d) {
	return d.size() == 1 && isnan(d[0].a.x);
}

/**
 * Intersection of ordered half plane sets.
 * Each set must be sorted by polar angle.
 * Empty sets have the meaning of the whole plane.
 * Complexity: O(n * log(k)).
 */
darr<line> intersect(darr<darr<line> > d) {

	// Compare last elements by polar angle.
	struct cmp {
		bln operator()(const darr<line> *a, const darr<line> *b) const {
			return vt(a->back().a, a->back().b).ls_ang(
				vt(b->back().a, b->back().b));
		}
	};
	
	heap<darr<line>*, singleton<resizer<darr<line>*>>,
			singleton<allocator<darr<line>*>>,
			singleton<cmp>> h;

	// Push each set to heap.
	for (uigr i = 0; i < d.size(); ++i)
		if (d[i].size() > 0) {
			if (isnan(d[i][0].a.x))
				return darr<line>(1, line(VT_NAN, VT_NAN));
			h.insert(&d[i]);
		}

	if (h.size() == 0)
		return darr<line>();

	darr<line> b;

	// Push all half planes in b in sorted order.
	// And remove useless half planes with same polar angle.
	while (h.size() > 0) {

		darr<line> &a = *h.get_min();
		h.erase_min();

		if (b.size() > 0 && vt(b.back().a, b.back().b).eq_ang(
				vt(a.back().a, a.back().b))) {

			if (ep(vt(b.back().a, b.back().b) %
					vt(b.back().a, a.back().a)) > 0) {
				b.pop();
				b.push(a.back());
			}
		} else
			b.push(a.back());

		a.pop();
		if (a.size() > 0)
			h.insert(&a);
	}

	darr<line> c;
	c.push(b[0]);
	
	// -1 - empty set.
	// 0 - line b is useless.
	// 1 - line b is useful.
	struct {
		chr operator()(line a, line b, line c) const {

			if (a == c)
				return vt(a.a, a.b) % vt(a.a, b.a) >= 0 ? 1 : -1;

			vt p = a & c;

			if (isinf(p.x))
				// Epsilon is useless because value != 0.
				return vt(a.a, a.b) % vt(a.a, c.a) < 0 ? -1 : 1;
			if (isnan(p.x))
				return 1;

			// Epsilon is useless because value != 0.
			dbl d = vt(a.b, a.a) % vt(c.a, c.b) < 0 ? 1.0 : -1.0;
			ray r1 = ray(p, p + vt(a.b, a.a) * d),
				r2 = ray(p, p + vt(c.a, c.b) * d);

			vt p1 = r1 & b, p2 = r2 & b;
			if (isinf(p1.x) && isinf(p2.x))
				// Epsilon is useless because value != 0.
				return vt(b.a, b.b) % vt(b.a, p) > 0 ? 0 : -1;
			return 1;
		}
	} intersect_useless;

	for (uigr i = 1; i < b.size(); ++i)
		switch (intersect_useless(c.back(), b[i], b[(i + 1) %
				b.size()])) {
		case chr(-1):
			return darr<line>(1, line(VT_NAN, VT_NAN));
		case 1:
			c.push(b[i]);
		}

	uigr l = 0, r = c.size() - 1;
	while (l != r) {
		switch (intersect_useless(c[r], c[l], c[l + 1])) {
			case chr(-1):
				return darr<line>(1, line(VT_NAN, VT_NAN));
			case 0:
				++l;
				continue;
		}
		if (l == r)
			break;
		switch (intersect_useless(c[r - 1], c[r], c[l])) {
			case chr(-1):
				return darr<line>(1, line(VT_NAN, VT_NAN));
			case 0:
				--r;
				continue;
		}
		break;
	}

	c.cshift(l);
	c.pop(l + c.size() - 1 - r);

	return c;
}

/**
 * Intersection of convexes.
 * Complexity: O(n * log(k)).
 */
cvx intersect(darr<cvx> c) {
	
	darr<darr<line> > d(c.size());
	for (uigr i = 0; i < c.size(); ++i) {
		c[i].clean();
		c[i].sort_ang();
		if (c[i].size() == 0)
			return cvx();
		if (c[i].size() == 1) {
			d[i].push(line(c[i][0], c[i][0] + vt(1, 0)));
			d[i].push(line(c[i][0], c[i][0] + vt(-1, 1)));
			d[i].push(line(c[i][0], c[i][0] + vt(0, -1)));
		} else if (c[i].size() == 2) {
			d[i].push(line(c[i][0], c[i][1]));
			d[i].push(line(c[i][1], c[i][1] + vt(c[i][0],
					c[i][1]).rot90()));
			d[i].push(line(c[i][1], c[i][0]));
			d[i].push(line(c[i][0], c[i][0] + vt(c[i][1],
					c[i][0]).rot90()));
			if (ep(vt(0, 1) % vt(c[i][0], c[i][1])) >= 0)
				d[i].cshift(-1);
		} else
			for (uigr j = c[i].size() - 1; j < c[i].size(); --j)
				d[i].push(line(c[i][j], c[i][(j + 1) % c[i].size()]));
	}
	darr<line> a = intersect(d);
	if (isempty(a))
		return cvx();
	cvx b(a.size());
	for (uigr i = 0; i < a.size(); ++i)
		b[i] = a[i] & a[(i + 1) % a.size()];
	
	return b;
}

/**
 * Graham scan.
 */
cvx graham_scan(pgn a) {
	
	struct cmp {
	
		vt p;
	
		bln operator()(vt a, vt b) const {
			a = vt(p, a);
			b = vt(p, b);
			return ep(a % b) > 0 ||
					ep(a % b) == 0 &&
					ep(a.abs2()) < b.abs2();
		}
	};

	if (a.size() == 0)
		return cvx();
	a.clean();
	
	thread_local_singleton<cmp>::value.p = a[0];
	for (uigr i = 1; i < a.size(); ++i)
		thread_local_singleton<cmp>::value.p =
				min(thread_local_singleton<cmp>::value.p, a[i]);
	quick_sort<vt, thread_local_singleton<cmp>>(a.data(), a.size());
	cvx c;
	c.push(a[0]);
	for (uigr i = 1; i < a.size(); ++i) {
		while (c.size() > 1 &&
				ep(vt(c.back(1), c.back()) % vt(c.back(1), a[i])) <= 0)
			c.pop();
		c.push(a[i]);
	}
	while (c.size() > 1 &&
			ep(vt(c.back(1), c.back()) % vt(c.back(1), a[0])) < 0)
		c.pop();
		
	return c;
}