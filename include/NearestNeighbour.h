#pragma once
#include "Algorithm.h"

class NearestNeighbour
	: public Algorithm
{
public:
	NearestNeighbour(Problem* p);
	std::vector<int> solve() override;
};