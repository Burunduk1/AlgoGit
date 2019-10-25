/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cassert>
#include <algorithm>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

struct Timer {
	double ticks;
	Timer() : ticks(clock()) { }
	double sec() {
		return (clock() - ticks) / CLOCKS_PER_SEC;
	}
} t;

template<class Test, class Solution>
double launch(Test test, Solution solve) {
	Timer timer;
	solve(test);
	return timer.sec();
}

template<class Test, class Solution>
std::pair<double, typename Test::Answer> launch_with_answer(Test test, Solution solve) {
	Timer timer;
	auto answer = solve(test);
	return {timer.sec(), answer};
}

template<class Test, class Solution>
void test_TL(Test test, Solution solve) {
	double time = launch(test, solve);
	err("%.3f sec: %s\n", time, solve.name);
}

template<class Test, class Solution>
void test_WA(Test test, Solution solve) {
	auto [time, output] = launch_with_answer(test, solve);
	err("%s: ", solve.name);
	assert(test.check(output));
	err("OK\n");
}

template<class Test, class Solution>
void test_WA_TL(Test test, Solution solve) {
	auto [time, output] = launch_with_answer(test, solve);
	err("%.3f sec: %s, ", time, solve.name);
	assert(test.check(output));
	err("OK\n");
}
