#include "Application.h"

Application::Application(const std::string& file_name)
{
	this->loadProblems(file_name);
}

void Application::run()
{
	if (this->problems.size() != 0)
	{
		for (auto& problem : this->problems)
		{
			problem->printProblem();
			delete problem;
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
