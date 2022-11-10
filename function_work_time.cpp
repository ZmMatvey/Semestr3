#include "function_work_time.h"
#include <iostream>

function_work_time::function_work_time() {
	start = std::chrono::high_resolution_clock::now();
}

function_work_time::~function_work_time() {
	finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = finish - start;
	std::cout << time.count() << std::endl;
}
