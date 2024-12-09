cmake_minimum_required (VERSION 3.8)

project ("TSP")

add_executable (TSP "main.cpp"  "Problem.h" "Problem.cpp" "Algorithm.h" "Algorithm.cpp"   "DynamicProgramming.h" "DynamicProgramming.cpp" "Greedy.h" "Greedy.cpp" "GreedyRandomized.h" "GreedyRandomized.cpp" "NearestNeighbour.h" "NearestNeighbour.cpp" "SimulatedAnnealing.h" "SimulatedAnnealing.cpp")