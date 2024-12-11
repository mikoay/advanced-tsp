#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(Problem* p)
{
    this->problem = p;
}

void DynamicProgramming::solve()
{
    const int INF = std::numeric_limits<int>::max();
    unsigned int n = this->problem->n;
    const auto& d = this->problem->d;
    const auto& t = this->problem->t;
    unsigned int z = this->problem->z;
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
        std::cout << "Brak dopuszczalnego rozwiazania" << std::endl;
        return;
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
    std::cout << "====DYNAMIC PROGRAMMING====" << std::endl;
    std::cout << "Minimalny dystans: " << min_distance << std::endl;
    std::cout << "Sciezka: ";
    for (int city : path) 
    {
        std::cout << city << " ";
    }
    std::cout << std::endl;
}