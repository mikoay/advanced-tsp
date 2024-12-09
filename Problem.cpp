#include "Problem.h"

Problem::Problem()
{
	this->n = 0;
	this->d = {};
	this->t = {};
	this->z = 0;
}

Problem::Problem(unsigned int a, std::vector<std::vector<int>> b, std::vector<std::pair<int, int>> c, unsigned int d)
{
	this->n = a;
	this->d = b;
	this->t = c;
	this->z = d;
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

void Problem::printProblem() const
{
	this->printN();
	this->printD();
	this->printT();
	this->printZ();
}
