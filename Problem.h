#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>

class Problem
{
public:
	unsigned int n;
	std::vector<std::vector<int>> d;
	std::vector<std::pair<int, int>> t;
	unsigned int z;
	Problem();
	Problem(unsigned int a, std::vector<std::vector<int>> b, std::vector<std::pair<int, int>> c, unsigned int d);
	~Problem();
	void generateInstance(unsigned int n, unsigned int distanceStartRange, unsigned int distanceStopRange, unsigned int minWindowWidth, unsigned int maxWindowWidth, unsigned int timeMargin);
	void printProblem() const;
	bool solvable;
private:
	std::vector<int> optimal_route;
	unsigned int optimal_route_distance;
	void printN() const;
	void printD() const;
	void printT() const;
	void printZ() const;
	std::vector<int> getOptimalRoute();
};