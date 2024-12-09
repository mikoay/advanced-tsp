#include "Problem.h"
#include "DynamicProgramming.h"
#include "Greedy.h"

int main()
{
	Problem* tsp = new Problem(5, { {0, 10, 20, 30, 40}, {10, 0, 25, 35, 20}, {20, 25, 0, 15, 25}, {30, 35, 15, 0, 10}, {40, 20, 25, 10, 0} }, { {0, 50}, {70, 100}, {50, 80}, {10, 40}, {35, 65} }, 100);
	tsp->generateInstance(3, 0, 50, 20, 60, 10);
	tsp->printProblem();
	DynamicProgramming* solver = new DynamicProgramming;
	solver->problem = tsp;
	solver->solve();
	delete tsp;
	return 0;
}