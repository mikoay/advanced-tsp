#include "NearestNeighbour.h"

NearestNeighbour::NearestNeighbour(Problem* p)
{
	this->problem = p;
}

std::vector<int> NearestNeighbour::solve()
{
    if (this->problem->n <= 0)
    {
        return {};
    }
    if (this->problem->n == 1)
    {
        return { 0, 0 };
    }
    std::vector<int> route;
    std::vector<bool> visited(problem->n, false);
    int current_city = 0;
    route.push_back(current_city);
    visited[current_city] = true;
    int current_time = 0;
    int total_distance = 0;
    int remaining_fuel = problem->z;
    while (route.size() < problem->n) 
    {
        int next_city = -1;
        int min_distance = std::numeric_limits<int>::max();
        for (int j = 0; j < problem->n; ++j) 
        {
            if (!visited[j] && problem->d[current_city][j] <= remaining_fuel) 
            {
                int arrival_time = current_time + problem->d[current_city][j];
                if (arrival_time >= problem->t[j].first && arrival_time <= problem->t[j].second) 
                {
                    if (problem->d[current_city][j] < min_distance) 
                    {
                        min_distance = problem->d[current_city][j];
                        next_city = j;
                    }
                }
            }
        }
        if (next_city == -1) 
        {
            return {};
        }
        route.push_back(next_city);
        visited[next_city] = true;
        current_time += problem->d[current_city][next_city];
        total_distance += problem->d[current_city][next_city];
        remaining_fuel -= problem->d[current_city][next_city];
        current_city = next_city;
    }
    if (problem->d[current_city][0] <= remaining_fuel) 
    {
        total_distance += problem->d[current_city][0];
        route.push_back(0);
    }
    else 
    {
        return {};
    }
    return route;
}