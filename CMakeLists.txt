cmake_minimum_required (VERSION 3.8)

project ("TSP")

include_directories(include)

add_executable (TSP "main.cpp" "include/Application.h" "src/Application.cpp" "include/Problem.h" "src/Problem.cpp" "include/Algorithm.h" "src/Algorithm.cpp" "include/DynamicProgramming.h" "src/DynamicProgramming.cpp" "include/Greedy.h" "src/Greedy.cpp" "include/GreedyRandomized.h" "src/GreedyRandomized.cpp" "include/NearestNeighbour.h" "src/NearestNeighbour.cpp" "include/SimulatedAnnealing.h" "src/SimulatedAnnealing.cpp" "include/Benchmark.h" "src/Benchmark.cpp" "include/json.hpp")
add_executable (Tests "QualityTests.cpp" "include/Problem.h" "src/Problem.cpp" "include/Algorithm.h" "src/Algorithm.cpp" "include/DynamicProgramming.h" "src/DynamicProgramming.cpp" "include/Greedy.h" "src/Greedy.cpp" "include/GreedyRandomized.h" "src/GreedyRandomized.cpp" "include/NearestNeighbour.h" "src/NearestNeighbour.cpp" "include/SimulatedAnnealing.h" "src/SimulatedAnnealing.cpp" "include/catch.hpp")