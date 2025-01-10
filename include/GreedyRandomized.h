#pragma once
#include "Algorithm.h"
#include <random>
#include <algorithm>

class GreedyRandomized
	: public Algorithm
{
public:
	GreedyRandomized(Problem* p);
	std::vector<int> solve(bool stats) override;
};