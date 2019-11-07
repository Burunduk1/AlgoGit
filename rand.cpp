#include <bits/stdc++.h>

using namespace std;

unsigned R() { return (rand() << 15) ^ rand(); }
int rndInt( int n ) { return R() % n; }

mt19937 rnd1(239);
mt19937 rnd2(chrono::system_clock::now().time_since_epoch().count()); // seed = time

int main() {
	uniform_real_distribution<double> gen_double(2, 3); // double [2..3]
	uniform_int_distribution<int> gen_int(2, 3); // int [2..3]
	cout << gen_double(rnd2) << endl;
	cout << gen_int(rnd2) << endl;

	int n = 10, p[n];
	shuffle(p, p + n, mt19937(239));
}
