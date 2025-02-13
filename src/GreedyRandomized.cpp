#include "GreedyRandomized.h"

GreedyRandomized::GreedyRandomized(Problem* p)
{
    this->name = "Greedy Randomized";
    this->problem = p;
}

std::vector<int> GreedyRandomized::solve(bool stats)
{
    clock_t startTime = clock();
    size_t startMem = this->getMemoryUsage();
    if (this->problem->n <= 0)
    {
        clock_t endTime = clock();
        size_t endMem = this->getMemoryUsage();
        double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
        size_t totalMem = endMem - startMem;
        if (stats)
        {
            this->benchmarkSummary(totalTime, totalMem);
        }
        return {};
    }
    if (this->problem->n == 1)
    {
        clock_t endTime = clock();
        size_t endMem = this->getMemoryUsage();
        double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
        size_t totalMem = endMem - startMem;
        if (stats)
        {
            this->benchmarkSummary(totalTime, totalMem);
        }
        return { 0, 0 };
    }
    std::vector<int> route;
    std::vector<bool> visited(problem->n, false);
    int current_city = 0;
    route.push_back(current_city);
    visited[current_city] = true;
    int current_time = 0;
    int total_distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 1; i < problem->n; ++i) 
    {
        std::vector<int> candidates;
        int min_distance = std::numeric_limits<int>::max();
        for (int j = 1; j < problem->n; ++j) 
        {
            if (!visited[j] && problem->t[j].first <= current_time + problem->d[current_city][j] && current_time + problem->d[current_city][j] <= problem->t[j].second) 
            {
                candidates.push_back(j);
                min_distance = std::min(min_distance, problem->d[current_city][j]);
            }
        }
        if (candidates.empty()) 
        {
            clock_t endTime = clock();
            size_t endMem = this->getMemoryUsage();
            double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
            size_t totalMem = endMem - startMem;
            if (stats)
            {
                this->benchmarkSummary(totalTime, totalMem);
            }
            return {};
        }
        int next_city;
        std::vector<int> close_candidates;
        for (int candidate : candidates) 
        {
            if (problem->d[current_city][candidate] <= min_distance + 10) 
            {
                close_candidates.push_back(candidate);
            }
        }
        std::uniform_int_distribution<int> dist(0, close_candidates.size() - 1);
        next_city = close_candidates[dist(gen)];
        route.push_back(next_city);
        visited[next_city] = true;
        current_city = next_city;
        current_time += problem->d[route[route.size() - 2]][current_city];
        total_distance += problem->d[route[route.size() - 2]][current_city];
    }
    total_distance += problem->d[current_city][0];
    route.push_back(0);
    if (total_distance > problem->z)
    {
        clock_t endTime = clock();
        size_t endMem = this->getMemoryUsage();
        double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
        size_t totalMem = endMem - startMem;
        if (stats)
        {
            this->benchmarkSummary(totalTime, totalMem);
        }
        return {};
    }
    clock_t endTime = clock();
    size_t endMem = this->getMemoryUsage();
    double totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    size_t totalMem = endMem - startMem;
    if (stats)
    {
        this->benchmarkSummary(totalTime, totalMem);
    }
    return route;
}