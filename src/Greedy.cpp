#include "Greedy.h"

Greedy::Greedy(Problem* p)
{
    this->problem = p;
}

std::vector<int> Greedy::solve()
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
    for (int i = 1; i < problem->n; ++i) 
    {
        int next_city = -1;
        int min_distance = std::numeric_limits<int>::max();
        for (int j = 1; j < problem->n; ++j) {
            if (!visited[j] && problem->t[j].first <= current_time + problem->d[current_city][j] && current_time + problem->d[current_city][j] <= problem->t[j].second) 
            {
                if (problem->d[current_city][j] < min_distance) 
                {
                    min_distance = problem->d[current_city][j];
                    next_city = j;
                }
            }
        }
        if (next_city == -1) 
        {
            return {};
        }
        route.push_back(next_city);
        visited[next_city] = true;
        current_city = next_city;
        current_time += min_distance;
        total_distance += min_distance;
    }
    if (problem->d[current_city][0] <= problem->z) 
    {
        total_distance += problem->d[current_city][0];
        route.push_back(0);
    }
    if (total_distance > this->problem->z)
    {
        return {};
    }
    return route;
}