#pragma once
#define NOMINMAX
#include "Problem.h"
#include <windows.h>
#include <psapi.h>

class Algorithm
{
public:
	std::string name;
	Problem* problem;
	virtual std::vector<int> solve(bool stats) = 0;
	Algorithm();
	~Algorithm();
	size_t getMemoryUsage();
	void benchmarkSummary(double time, size_t memory);
};