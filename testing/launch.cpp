/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cstdio>
#include <ctime>
#include <cstdarg>

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
void testTL(Test test, Solution solve) {
	double time = launch(test, solve);
	printf("%.3f sec: %s\n", time, solve.name);
}
