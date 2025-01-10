#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Problem.h"
#include "DynamicProgramming.h"
#include "Greedy.h"
#include "GreedyRandomized.h"
#include "NearestNeighbour.h"
#include "SimulatedAnnealing.h"

TEST_CASE("Test dla pustego problemu")
{
	Problem* problem = new Problem(0, {}, {}, 0);
	std::vector<Algorithm*> algorithms = {
		new DynamicProgramming(problem),
		new Greedy(problem),
		new GreedyRandomized(problem),
		new NearestNeighbour(problem),
		new SimulatedAnnealing(problem, 1000, 0.95, 1000)
	};
	for (auto& algorithm : algorithms)
	{
		REQUIRE(algorithm->solve(false) == std::vector<int>{});
	}
}

TEST_CASE("Test dla problemu z jednym miastem")
{
	Problem* problem = new Problem(1, {{0}}, {{0, 0}}, 0);
	std::vector<Algorithm*> algorithms = {
		new DynamicProgramming(problem),
		new Greedy(problem),
		new GreedyRandomized(problem),
		new NearestNeighbour(problem),
		new SimulatedAnnealing(problem, 1000, 0.95, 1000)
	};
	for (auto& algorithm : algorithms)
	{
		REQUIRE(algorithm->solve(false) == std::vector<int>{0, 0});
	}
}

TEST_CASE("Test dla malych instancji problemow")
{
	std::vector<std::pair<Problem*, std::vector<int>>> problems = {
		{new Problem(3, {{0, 15, 25}, {15, 0, 10}, {25, 10, 0}}, {{0, 10}, {25, 45}, {20, 40}}, 55), {0, 2, 1, 0}},
		{new Problem(4, {{0, 15, 40, 25}, {15, 0, 10, 20}, {40, 10, 0, 30}, {25, 20, 30, 0}}, {{0, 5}, {40, 80}, {30, 45}, {50, 100}}, 100), {0, 2, 1, 3, 0}},
		{new Problem(5, {{0, 15, 5, 10, 30}, {15, 0, 35, 10, 20}, {5, 35, 0, 30, 25}, {10, 10, 30, 0, 15}, {30, 20, 25, 15, 0}}, {{0, 20}, {10, 40}, {50, 90}, {80, 120}, {40, 95}}, 110), {0, 1, 2, 4, 3, 0}}
	};
	for (auto& problem : problems)
	{
		std::vector<Algorithm*> algorithms = {
			new DynamicProgramming(problem.first),
			new Greedy(problem.first),
			new GreedyRandomized(problem.first),
			new NearestNeighbour(problem.first),
			new SimulatedAnnealing(problem.first, 1000, 0.95, 1000)
		};
		for (auto& algorithm : algorithms)
		{
			REQUIRE(algorithm->solve(false) == problem.second);
		}
	}
}

TEST_CASE("Test niespelnialnosci")
{
	std::vector<Problem*> problems = {
		new Problem(3, {{0, 15, 25}, {15, 0, 10}, {25, 10, 0}}, {{0, 10}, {25, 45}, {20, 40}}, 30),
		new Problem(4, {{0, 15, 40, 25}, {15, 0, 10, 20}, {40, 10, 0, 30}, {25, 20, 30, 0}}, {{0, 5}, {40, 80}, {30, 45}, {50, 100}}, 80),
		new Problem(5, {{0, 15, 5, 10, 30}, {15, 0, 35, 10, 20}, {5, 35, 0, 30, 25}, {10, 10, 30, 0, 15}, {30, 20, 25, 15, 0}}, {{0, 20}, {10, 20}, {50, 60}, {80, 90}, {40, 45}}, 110)
	};
	for (auto& problem : problems)
	{
		std::vector<Algorithm*> algorithms = {
			new DynamicProgramming(problem),
			new Greedy(problem),
			new GreedyRandomized(problem),
			new NearestNeighbour(problem),
			new SimulatedAnnealing(problem, 1000, 0.95, 1000)
		};
		for (auto& algorithm : algorithms)
		{
			REQUIRE(algorithm->solve(false) == std::vector<int>{});
		}
	}
}

TEST_CASE("Test deterministycznosci")
{
	std::vector<Problem*> problems = {
	new Problem(3, {{0, 15, 25}, {15, 0, 10}, {25, 10, 0}}, {{0, 10}, {25, 45}, {20, 40}}, 30),
	new Problem(4, {{0, 15, 40, 25}, {15, 0, 10, 20}, {40, 10, 0, 30}, {25, 20, 30, 0}}, {{0, 5}, {40, 80}, {30, 45}, {50, 100}}, 80),
	new Problem(5, {{0, 15, 5, 10, 30}, {15, 0, 35, 10, 20}, {5, 35, 0, 30, 25}, {10, 10, 30, 0, 15}, {30, 20, 25, 15, 0}}, {{0, 20}, {10, 20}, {50, 60}, {80, 90}, {40, 45}}, 110)
	};
	unsigned short int num_of_tests = 5;
	for (auto& problem : problems)
	{
		std::vector<Algorithm*> algorithms = {
			new DynamicProgramming(problem),
			new Greedy(problem),
			new GreedyRandomized(problem),
			new NearestNeighbour(problem),
			new SimulatedAnnealing(problem, 1000, 0.95, 1000)
		};
		for (auto& algorithm : algorithms)
		{
			std::vector<int> first_solution = algorithm->solve(false);
			bool same = true;
			for (int i = 0; i < num_of_tests; i++)
			{
				if (algorithm->solve(false) != first_solution)
				{
					same = false;
					break;
				}
			}
			REQUIRE(same);
		}
	}
}

TEST_CASE("Test losowosci")
{
	std::vector<Problem*> problems = {
	new Problem(3, {{0, 15, 25}, {15, 0, 10}, {25, 10, 0}}, {{0, 10}, {25, 45}, {20, 40}}, 30),
	new Problem(4, {{0, 15, 40, 25}, {15, 0, 10, 20}, {40, 10, 0, 30}, {25, 20, 30, 0}}, {{0, 5}, {40, 80}, {30, 45}, {50, 100}}, 80),
	new Problem(5, {{0, 15, 5, 10, 30}, {15, 0, 35, 10, 20}, {5, 35, 0, 30, 25}, {10, 10, 30, 0, 15}, {30, 20, 25, 15, 0}}, {{0, 20}, {10, 20}, {50, 60}, {80, 90}, {40, 45}}, 110)
	};
	unsigned short int num_of_tests = 5;
	for (auto& problem : problems)
	{
		std::vector<Algorithm*> algorithms = {
			new DynamicProgramming(problem),
			new Greedy(problem),
			new GreedyRandomized(problem),
			new NearestNeighbour(problem),
			new SimulatedAnnealing(problem, 1000, 0.95, 1000)
		};
		for (auto& algorithm : algorithms)
		{
			std::vector<int> first_solution = algorithm->solve(false);
			bool different = true;
			for (int i = 0; i < num_of_tests; i++)
			{
				if (algorithm->solve(false) == first_solution)
				{
					different = false;
					break;
				}
			}
			REQUIRE(different);
		}
	}
}