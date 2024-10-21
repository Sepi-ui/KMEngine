#define SDL_MAIN_HANDLED

#ifdef _WIN32
	#include <windows.h>
	#include <psapi.h>
#endif

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/entity.h"
#include "logIt.h"
#include "../../include/performanceFunctions.h"
#include <SDL3/SDL.h>
#define MAX_TESTS 10

typedef struct PerformanceTest {
	int index;
	const char* name;
	void (*run)(int load, int iteration);
}PerformanceTest;

PerformanceTest tests[MAX_TESTS];
int num_tests = 0;

void register_test(int index, const char* name, void (*run)(int load, int iteration)) {
if (num_tests < MAX_TESTS) { 
	tests[num_tests].index = index;
	tests[num_tests].name = name;
	tests[num_tests].run = run;
	num_tests++;
	}else{
	error_log("Max number of tests reached\n");
	};
}

void run_selected_test(const char* tokenList, int load, int iteration) {
char* token = strtok(tokenList, ",");
while (token != NULL) {
	int index = atoi(token);
	for (int i = 0; i < num_tests; i++) {
		if (tests[i].index == index) {
			info_log("running %s with load: %d, iteration: %d\n",tests[i].name, load, iteration);
			tests[i].run(load, iteration);
			break;
		};
	};
	token = strtok(NULL, ",");


};
}

void register_all_tests() {
	    register_test(1, "collision_test", collision_performance_test);
	        register_test(2, "rendering_test", rendering_performance_test);
		    register_test(3, "physics_test", physics_performance_test);
}








int main(int argc, char* argv[]) {
	initializeLogStreams();
	    if (argc < 4) {
		info_log("Usage: %s <test_indices> <load> <iterations>\n", argv[0]);
		return 1;
		}

	        const char* selected_tests = argv[1];
		int load = atoi(argv[2]);
	        int iterations = atoi(argv[3]);

		// Register all performance tests
		register_all_tests();

		//List all available tests for user information
		info_log("Available Tests:\n");
		for (int i = 0; i < num_tests; i++) {
		info_log("%d. %s\n", tests[i].index, tests[i].name);
		}

		// Run the selected tests
		run_selected_test(selected_tests, load, iterations);

		return 0;
}
