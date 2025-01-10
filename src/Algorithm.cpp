#include "Algorithm.h"

Algorithm::Algorithm()
{
	this->problem = nullptr;
}

Algorithm::~Algorithm()
{
}

size_t Algorithm::getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return memInfo.WorkingSetSize;
    }
    return 0;
}

void Algorithm::benchmarkSummary(double time, size_t memory)
{
    std::cout << "==========Algorithm: " << this->name << "==========" << std::endl;
    std::cout << "Total execution time: " << time << " s" << std::endl;
    std::cout << "Total memory used: " << double(memory / 1024.0) << " KB" << std::endl;
}