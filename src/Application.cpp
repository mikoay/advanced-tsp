#include "Application.h"

Application::Application(const std::string& file_name)
{
	this->loadProblems(file_name);
}

Application::~Application()
{
    this->saveProblems("results.json");
    if (this->problems.size() != 0)
    {
        for (auto& problem : this->problems)
        {
            delete problem;
        }
        this->problems.clear();
    }
}

void Application::run()
{
	if (this->problems.size() != 0)
	{
		for (auto& problem : this->problems)
		{
			problem->printProblem();
            std::vector<Algorithm*> solvers = {
                new DynamicProgramming(problem),
                new Greedy(problem),
                new GreedyRandomized(problem),
                new NearestNeighbour(problem),
                new SimulatedAnnealing(problem, 1000, 0.95, 1000)
            };
            for (auto& algorithm : solvers)
            {
                algorithm->solve(true);
            }
		}
	}
}

void Application::loadProblems(const std::string& file_name)
{
	std::ifstream file("../../../" + file_name);
	json j;
	file >> j;
	for (const auto& problem_json : j["problems"]) {
		Problem* problem = new Problem();
		problem->n = problem_json["n"];
		problem->d = problem_json["d"].get<std::vector<std::vector<int>>>();
		auto t = problem_json["t"].get<std::vector<std::vector<int>>>();
		for (const auto& w : t) {
			problem->t.emplace_back(w[0], w[1]);
		}
		problem->z = problem_json["z"];
		this->problems.push_back(problem);
	}
	file.close();
}

void Application::saveProblems(const std::string& file_name)
{
    json output_json;
    for (auto& problem : this->problems) 
    {
        json problem_json;
        problem_json["n"] = problem->n;
        problem_json["d"] = problem->d;
        std::vector<std::vector<int>> time_windows;
        for (const auto& window : problem->t) 
        {
            time_windows.push_back(std::vector<int>{window.first, window.second});
        }
        problem_json["t"] = time_windows;
        problem_json["z"] = problem->z;
        std::vector<Algorithm*> solvers = {
            new DynamicProgramming(problem),
            new Greedy(problem),
            new GreedyRandomized(problem),
            new NearestNeighbour(problem),
            new SimulatedAnnealing(problem, 1000, 0.95, 1000)
        };
        for (auto& algorithm : solvers)
        {
            problem_json["solutions"][algorithm->name] = algorithm->solve(false);
        }
        output_json["problems"].push_back(problem_json);
    }
    std::ofstream file("../../../" + file_name);
    if (file.is_open()) 
    {
        file << output_json.dump(4);
        file.close();
    }
}