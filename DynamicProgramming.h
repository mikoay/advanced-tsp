#pragma once
#include "Algorithm.h"

class DynamicProgramming
	: public Algorithm
{
public:
	DynamicProgramming(Problem* p);
	void solve() override;
};