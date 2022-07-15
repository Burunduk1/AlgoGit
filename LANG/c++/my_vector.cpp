#include <bits/stdc++.h>

using namespace std;

template <class T>
struct MyVector : vector<T> {
	MyVector(int n = 0) : vector<T>(n) { }
	T &operator [] (int i)       { return vector<T>::at(i); }
	T  operator [] (int i) const { return vector<T>::at(i); }
};

/** 
 * Если вместо всех int[] и vector<int> использовать MyVector<int>,
 * всплывут все range check error-ы 
 * 
 * Аналогично #define _GLIBCXX_DEBUG для g++
 */
MyVector<int> b(10), a;

int main() {
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	printf("%d\n", a[0]);
	printf("%d\n", a[1]);
	printf("%d\n", a[2]);
	printf("%d\n", a[3]);
}
