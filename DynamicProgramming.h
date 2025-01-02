#pragma once
#include "Algorithm.h"

class DynamicProgramming
	: public Algorithm
{
public:
	DynamicProgramming(Problem* p);
	std::vector<int> solve() override;
};