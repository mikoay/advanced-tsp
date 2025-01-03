#pragma once

#include <ctime>
#include "Problem.h"
#include "DynamicProgramming.h"
#include "Greedy.h"
#include "GreedyRandomized.h"
#include "NearestNeighbour.h"
#include "SimulatedAnnealing.h"

class Test
{
public:
	Test(unsigned int input_n);
	void test();
private:
	std::vector<Algorithm*> solvers;
	Problem* problem;
	unsigned int n;
};