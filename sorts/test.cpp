/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <iostream>
#include <iterator>
#include <algorithm>

#include "../testing/launch.cpp"
#include "qsort.cpp"
#include "msort.cpp"

using namespace std;

struct Test {
	using Answer = vector<int>;
	vector<int> a, answer;
	Test(int n) : a(n) {
		mt19937 rnd;
		for (int &x : a)
			x = rnd();
		answer = a;
		std::sort(answer.begin(), answer.end());
	}
	void out_test() {
		copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")), cout << endl;
	}
	void out_answer() {
		copy(answer.begin(), answer.end(), ostream_iterator<int>(cout, " ")), cout << endl;
	}
	bool check(const Answer &output) {
		return output == answer;
	}
};

template<class Test>
struct Solution {
	typedef void (*SortFunction)(int*, int);
	SortFunction f;
	const char *name;
	typename Test::Answer operator() (Test &t) {
		f(t.a.data(), t.a.size());
		return std::move(t.a);
	}
};

void sort(int *a, int n) {
	std::sort(a, a + n);
}
void stable_sort(int *a, int n) {
	std::stable_sort(a, a + n);
}

int main() {
	int n;
	cin >> n;

	Test t(n);

	test_WA_TL(t, Solution<Test> {sort, "std::sort"});
	test_WA_TL(t, Solution<Test> {qsort_insertion<int>, "quick sort with median and insertion"});
	test_WA_TL(t, Solution<Test> {qsort<int>, "quick sort with median"});
	test_WA_TL(t, Solution<Test> {qsort_random<int>, "quick sort with random"});

	test_WA_TL(t, Solution<Test> {stable_sort, "std::stable_sort"});
	test_WA_TL(t, Solution<Test> {msort_insertion<int>, "merge sort with insertion"});
	test_WA_TL(t, Solution<Test> {msort<int>, "merge sort"});
}
