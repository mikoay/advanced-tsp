#pragma once
#include "Problem.h"

class Algorithm
{
public:
	Problem* problem;
	virtual std::vector<int> solve() = 0;
	Algorithm();
	~Algorithm();
};