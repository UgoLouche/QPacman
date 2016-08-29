#include "QPRandomManager.h"

QPRandomManager::QPRandomManager()
	: rndEngine(), intDistri(0, 10)
{
	std::random_device rd;
	rndEngine = std::mt19937(rd());
}

QPRandomManager::~QPRandomManager()
{
}

void QPRandomManager::setIntBounds(int min, int max)
{
	intDistri = std::uniform_int_distribution<int>(min, max);
}

int QPRandomManager::nextInt() const
{
	return intDistri(rndEngine);
}
