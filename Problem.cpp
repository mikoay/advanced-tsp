#include "Problem.h"

Problem::Problem()
{
	this->n = 0;
	this->d = {};
	this->t = {};
	this->z = 0;
    this->solvable = false;
}

Problem::Problem(unsigned int a, std::vector<std::vector<int>> b, std::vector<std::pair<int, int>> c, unsigned int d)
{
	this->n = a;
	this->d = b;
	this->t = c;
	this->z = d;
    this->solvable = false;
}

Problem::~Problem()
{
	this->d.clear();
	this->t.clear();
}

void Problem::generateInstance(unsigned int n, unsigned int distanceStartRange, unsigned int distanceStopRange, unsigned int minWindowWidth, unsigned int maxWindowWidth, unsigned int timeMargin)
{
	srand(time(NULL));
	this->n = n;
	this->d.clear();
	this->t.clear();
	for (size_t i = 0; i < n; i++)
	{
		this->d.push_back({});
		for (size_t j = 0; j < n; j++)
		{
			this->d[i].push_back(0);
		}
	}
	unsigned int totalDistance = 0, distance = 0;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (j > i)
			{
				do {
					distance = (rand() % (distanceStopRange - distanceStartRange + 1)) + distanceStartRange;
				} while (distance == 0);
				totalDistance += distance;
				this->d[i][j] = distance;
				this->d[j][i] = distance;
			}
		}
	}
	unsigned int base_time = 0, windowStart = 0, windowWidth = 0;
	for (size_t i = 0; i < n; i++)
	{
		base_time = this->d[0][i];
		windowStart = base_time + (rand() % timeMargin);
		windowWidth = (rand() % (maxWindowWidth - minWindowWidth + 1)) + minWindowWidth;
		this->t.push_back({ windowStart, windowStart + windowWidth });
	}
	this->z = totalDistance / (n * (n - 1) / 2) * 4;
    //this->optimal_route = this->getOptimalRoute();
    //if (this->optimal_route.size() == 0)
    //{
    //    this->optimal_route_distance = 0;
    //}
    //else
    //{
    //    for (int i = 0; i < this->optimal_route.size(); i++)
    //    {
    //        if (i + 1 == this->optimal_route.size())
    //        {
    //            this->optimal_route_distance += this->d[this->optimal_route[i]][0];
    //            break;
    //        }
    //        this->optimal_route_distance += this->d[this->optimal_route[i]][this->optimal_route[i + 1]];
    //    }
    //    solvable = true;
    //}
}

void Problem::printN() const
{
	std::cout << "N: " << this->n << std::endl;
}

void Problem::printD() const
{
	std::cout << "D:" << std::endl;
	for (size_t i = 0; i < this->d.size(); i++)
	{
		for (size_t j = 0; j < this->d[i].size(); j++)
		{
			std::cout << this->d[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Problem::printT() const
{
	std::cout << "T: " << std::endl;
	for (size_t i = 0; i < this->t.size(); i++)
	{
		std::cout << "(" << this->t[i].first << ", " << this->t[i].second << ")" << std::endl;
	}
}

void Problem::printZ() const
{
	std::cout << "Z: " << this->z << std::endl;
}

std::vector<int> Problem::getOptimalRoute()
{
    const int INF = std::numeric_limits<int>::max();
    unsigned int n = this->n;
    const auto& d = this->d;
    const auto& t = this->t;
    unsigned int z = this->z;
    std::vector<std::vector<int>> DP(1 << n, std::vector<int>(n, INF));
    std::vector<std::vector<int>> fuel(1 << n, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(1 << n, std::vector<int>(n, -1));
    DP[1][0] = 0;
    fuel[1][0] = 0;
    for (int state = 1; state < (1 << n); ++state)
    {
        for (int i = 0; i < n; ++i) {
            if (!(state & (1 << i)))
                continue;
            if (DP[state][i] == INF)
                continue;
            for (int j = 0; j < n; ++j)
            {
                if (state & (1 << j))
                    continue;
                int new_state = state | (1 << j);
                int arrival_time = DP[state][i] + d[i][j];
                int fuel_used = fuel[state][i] + d[i][j];
                if (fuel_used > z)
                    continue;
                if (arrival_time > t[j].second)
                    continue;
                if (arrival_time < t[j].first)
                {
                    arrival_time = t[j].first;
                }
                if (arrival_time < DP[new_state][j])
                {
                    DP[new_state][j] = arrival_time;
                    fuel[new_state][j] = fuel_used;
                    parent[new_state][j] = i;
                }
            }
        }
    }
    int final_state = (1 << n) - 1;
    int min_distance = INF;
    int last_city = -1;
    int total_fuel = INF;
    for (int i = 1; i < n; ++i)
    {
        if (DP[final_state][i] == INF || fuel[final_state][i] == INF)
            continue;
        int return_distance = DP[final_state][i] + d[i][0];
        int return_fuel = fuel[final_state][i] + d[i][0];
        if (return_fuel <= z && return_distance < min_distance)
        {
            min_distance = return_distance;
            last_city = i;
            total_fuel = return_fuel;
        }
    }
    if (min_distance == INF)
    {
        return {};
    }
    std::vector<int> path;
    int current_city = last_city;
    int current_state = final_state;
    while (current_city != -1)
    {
        path.push_back(current_city);
        int prev_city = parent[current_state][current_city];
        current_state &= ~(1 << current_city);
        current_city = prev_city;
    }
    reverse(path.begin(), path.end());
    path.push_back(0);
    return path;
}

void Problem::printProblem() const
{
	this->printN();
	this->printD();
	this->printT();
	this->printZ();
}
