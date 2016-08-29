#pragma once

#include <random>

class QPRandomManager
{
public:
	QPRandomManager();
	~QPRandomManager();

	//Random Int
	void setIntBounds(int min, int max);
	int nextInt() const;

private:
	mutable std::mt19937 rndEngine;

	std::uniform_int_distribution<int> intDistri;
};