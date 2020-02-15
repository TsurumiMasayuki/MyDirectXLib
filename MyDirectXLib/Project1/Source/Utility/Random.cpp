#include "Random.h"
#include <random>

Random::Random()
{
	std::random_device random;
	m_Seed = random();
}

Random::~Random()
{
}

int Random::getRandom(int min, int max)
{
	std::mt19937 random(m_Seed);
	std::uniform_int_distribution<int> distribition(min, max);
	return distribition(random);
}

float Random::getRandom(float min, float max)
{
	std::mt19937 random(m_Seed);
	std::uniform_real_distribution<float> distribition(min, max);
	return distribition(random);
}
