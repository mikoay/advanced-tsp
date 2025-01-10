#include "Benchmark.h"

Test::Test(unsigned int input_n)
{
	this->n = input_n;
	this->problem = new Problem(0, {}, {}, 0);
	this->solvers = {};
}

void Test::test()
{
	this->problem->generateInstance(this->n, 0, 100, 100, 200, 20);
	this->solvers = {
		new DynamicProgramming(this->problem),
		new Greedy(this->problem),
		new GreedyRandomized(this->problem),
		new NearestNeighbour(this->problem),
		new SimulatedAnnealing(this->problem, 1000, 0.95, 1000)
	};
	for (auto& algorithm : solvers)
	{
		algorithm->solve(true);
	}
}