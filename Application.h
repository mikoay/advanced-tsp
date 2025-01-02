#pragma once
#include <fstream>
#include "Problem.h"
#include "DynamicProgramming.h"
#include "Greedy.h"
#include "GreedyRandomized.h"
#include "NearestNeighbour.h"
#include "SimulatedAnnealing.h"
#include "Test.h"
#include "json.hpp"

using json = nlohmann::json;

class Application
{
public:
	Application(const std::string& file_name);
	void run();
private:
	std::vector<Problem*> problems;
	void loadProblems(const std::string& file_name);
};