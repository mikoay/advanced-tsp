#include "NearestNeighbour.h"

NearestNeighbour::NearestNeighbour(Problem* p)
{
	this->problem = p;
}

void NearestNeighbour::solve()
{
    std::vector<int> route;            // Trasa
    std::vector<bool> visited(problem->n, false);   // Wektor odwiedzonych miast

    int current_city = 0;   // Startujemy z miasta 0
    route.push_back(current_city);
    visited[current_city] = true;

    int current_time = 0;
    int total_distance = 0;
    int remaining_fuel = problem->z;

    for (int i = 1; i < problem->n; ++i) {
        int next_city = -1;
        int min_distance = std::numeric_limits<int>::max();

        // Szukamy najbli¿szego miasta spe³niaj¹cego warunki
        for (int j = 0; j < problem->n; ++j) {
            if (!visited[j] && problem->d[current_city][j] <= remaining_fuel &&
                current_time + problem->d[current_city][j] >= problem->t[j].first &&
                current_time + problem->d[current_city][j] <= problem->t[j].second) {
                if (problem->d[current_city][j] < min_distance) {
                    min_distance = problem->d[current_city][j];
                    next_city = j;
                }
            }
        }

        if (next_city == -1) {
            std::cerr << "No valid route found that respects the time windows and fuel limits." << std::endl;
            return;  // Brak dopuszczalnego rozwi¹zania
        }

        // Przemieszczamy siê do wybranego miasta
        route.push_back(next_city);
        visited[next_city] = true;
        current_time += problem->d[current_city][next_city];
        total_distance += problem->d[current_city][next_city];
        remaining_fuel -= problem->d[current_city][next_city];
        current_city = next_city;
    }

    // Powrót do miasta pocz¹tkowego
    if (problem->d[current_city][0] <= remaining_fuel &&
        current_time + problem->d[current_city][0] >= problem->t[0].first &&
        current_time + problem->d[current_city][0] <= problem->t[0].second) {
        total_distance += problem->d[current_city][0];
        route.push_back(0);
    }
    else {
        std::cerr << "No valid route found for return to city 0." << std::endl;
        return;  // Brak dopuszczalnego rozwi¹zania
    }

    // Wypisanie wyniku
    std::cout << "Optimal route: ";
    for (int city : route) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Minimal total distance (with return to city 0): " << total_distance << std::endl;
}