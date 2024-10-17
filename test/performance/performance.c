#define SDL_MAIN_HANDLED
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/entity.h"
#include "logIt.h"
#include <SDL3/SDL.h>
#define MAX_TESTS 10

typedef struct PerformanceTest {
	int index;
	const char* name;
	void (*run)(int load, int iteration);
}PerformanceTest;

PerformanceTest tests[MAX_TESTS];
int num_tests = 0;

void register_test(int index, const char* name, void (*run)(int load, int iteration) {
if (num_tests < MAX_TESTS) {
	tests[num_test].index = index;
	tests[num_test].name = name;
	tests[num_test].run = run;
	num_test++;
	}else{
	error_log("Max number of tests reached"\n);
	};
}
