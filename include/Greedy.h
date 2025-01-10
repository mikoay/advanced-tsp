#pragma once
#include "Algorithm.h"

class Greedy
	: public Algorithm
{
public:
	Greedy(Problem* p);
	std::vector<int> solve(bool stats) override;
};