#pragma once
#include "Algorithm.h"

class Greedy
	: public Algorithm
{
public:
	Greedy(Problem* p);
	void solve() override;
};