#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Problem* p, double it, double cr, double mi) 
{
	this->problem = p;
    this->initial_temperature = it;
    this->cooling_rate = cr;
    this->max_iterations = mi;
}

std::vector<int> SimulatedAnnealing::solve()
{
    srand(time(NULL));
    current_solution.resize(problem->n + 1);
    for (unsigned int i = 0; i < problem->n; ++i) 
    {
        current_solution[i] = i;
    }
    std::random_shuffle(current_solution.begin() + 1, current_solution.end() - 1);
    current_solution.back() = 0;
    best_solution = current_solution;
    best_distance = calculateDistance(current_solution);
    double temperature = initial_temperature;
    for (int iteration = 0; iteration < max_iterations; ++iteration) 
    {
        std::vector<int> new_solution = current_solution;
        swapCities(new_solution);
        int current_distance = calculateDistance(current_solution);
        int new_distance = calculateDistance(new_solution);
        if (new_distance != -1 && accept(current_distance, new_distance, temperature)) 
        {
            current_solution = new_solution;
            if (new_distance < best_distance || best_distance == -1) 
            {
                best_solution = new_solution;
                best_distance = new_distance;
            }
        }
        temperature *= cooling_rate;
    }
    if (best_distance == -1) 
    {
        return {};
    }
    else 
    {
        return best_solution;
    }
}

int SimulatedAnnealing::calculateDistance(const std::vector<int>& solution)
{
    int total_distance = 0;
    int remaining_fuel = problem->z;
    int current_time = 0;
    for (size_t i = 0; i < solution.size() - 1; ++i) 
    {
        int from = solution[i];
        int to = solution[i + 1];
        total_distance += problem->d[from][to];
        remaining_fuel -= problem->d[from][to];
        current_time += problem->d[from][to];
        if (to != 0 && (remaining_fuel < 0 || current_time < problem->t[to].first || current_time > problem->t[to].second)) 
        {
            return -1;
        }
    }
    int last_city = solution.back();
    total_distance += problem->d[last_city][0];
    remaining_fuel -= problem->d[last_city][0];
    if (remaining_fuel < 0) 
    {
        return -1;
    }
    return total_distance;
}

void SimulatedAnnealing::swapCities(std::vector<int>& solution)
{
    int i = rand() % (solution.size() - 2) + 1;
    int j = rand() % (solution.size() - 2) + 1;
    std::swap(solution[i], solution[j]);
}

bool SimulatedAnnealing::accept(int old_cost, int new_cost, double temperature)
{
    if (new_cost < old_cost) 
    {
        return true;
    }
    double probability = std::exp((old_cost - new_cost) / temperature);
    return (rand() / (RAND_MAX + 1.0)) < probability;
}