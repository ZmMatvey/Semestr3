#pragma once
#include <chrono>

class function_work_time
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start, finish;

public:
	function_work_time();

	~function_work_time();
};
