#include "Random.h"
#include <random>

Random::Random()
{
}

Random::~Random()
{
}

int Random::getRandom(int min, int max)
{
	std::random_device randomDevice;
	std::mt19937 random(randomDevice());
	std::uniform_int_distribution<int> distribition(min, max);
	return distribition(random);
}

float Random::getRandom(float min, float max)
{
	std::random_device randomDevice;
	std::mt19937 random(randomDevice());
	std::uniform_real_distribution<float> distribition(min, max);
	return distribition(random);
}
