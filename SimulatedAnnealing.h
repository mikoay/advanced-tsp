#pragma once
#include "Algorithm.h"
#include <random>

class SimulatedAnnealing
	: public Algorithm
{
public:
	double initial_temperature;
	double cooling_rate;
	int max_iterations;
	SimulatedAnnealing(Problem* p, double it, double cr, double mi);
	void solve() override;
private:
	std::vector<int> current_solution;
	std::vector<int> best_solution;
	int best_distance;
	int calculateDistance(const std::vector<int>& solution);
	void swapCities(std::vector<int>& solution);
	bool accept(int old_cost, int new_cost, double temperature);
};