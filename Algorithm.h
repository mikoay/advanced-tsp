#pragma once
#include "Problem.h"

class Algorithm
{
public:
	Problem* problem;
	virtual void solve() = 0;
	Algorithm();
	~Algorithm();
};