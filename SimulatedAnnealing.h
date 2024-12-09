#pragma once
#include "Algorithm.h"

class SimulatedAnnealing
	: public Algorithm
{
public:
	SimulatedAnnealing(Problem* p);
	void solve() override;
};