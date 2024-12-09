#include "Problem.h"
#include "DynamicProgramming.h"
#include "Greedy.h"
#include "GreedyRandomized.h"
#include "NearestNeighbour.h"
#include "SimulatedAnnealing.h"

int main()
{
	unsigned int n = 5;
	std::vector<std::vector<int>> d = {
		{0, 10, 20, 30, 40},
		{10, 0, 25, 35, 20},
		{20, 25, 0, 15, 25},
		{30, 35, 15, 0, 10},
		{40, 20, 25, 10, 0}
	};
	std::vector<std::pair<int, int>> t = {
		{0, 50},
		{70, 100},
		{50, 80},
		{10, 40},
		{35, 65}
	};
	unsigned int z = 100;
	Problem* tsp = new Problem(n, d, t, z);
	//tsp->generateInstance(4, 0, 50, 20, 60, 10);
	tsp->printProblem();
	std::vector<Algorithm*> solvers = {
		new DynamicProgramming(tsp),
		new Greedy(tsp),
		new GreedyRandomized(tsp),
		new NearestNeighbour(tsp)
	};
	//solvers.push_back(new NearestNeighbour);
	//solvers.push_back(new SimulatedAnnealing);
	for (auto &algorithm : solvers) {
		algorithm->solve();
	}
	delete tsp;
	return 0;
}