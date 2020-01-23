#include "GameTime.h"
#include <chrono>

//1.0f / 60.0f;
#define MIN_FRAME_TIME 0.0166f

float GameTime::timeScale = 1.0f;

float GameTime::deltaTime = 0.0f;

float GameTime::totalTime = 0.0f;
float GameTime::unscaledTotalTime = 0.0f;

long GameTime::curTime;
long GameTime::preTime;

void GameTime::update()
{
	updateDeltaTime();
	updateTotalTime();
}

void GameTime::addSleepTime(float value)
{
	deltaTime += value;
}

float GameTime::getDeltaTime()
{
	return deltaTime * std::fmaxf(timeScale, 0.0f);
}

float GameTime::getUnscaledDeltaTime()
{
	return deltaTime;
}

float GameTime::getTotalTime()
{
	return totalTime;
}

float GameTime::getUnscaledTotalTime()
{
	return unscaledTotalTime;
}

void GameTime::updateDeltaTime()
{
	auto now = std::chrono::system_clock::now();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	preTime = curTime;
	curTime = milliseconds.count();

	if (preTime == 0)
	{
		deltaTime = 0.0f;
		return;
	}

	deltaTime = curTime - preTime;
	deltaTime = deltaTime / 1000.0f;

	deltaTime = fminf(deltaTime, MIN_FRAME_TIME);
}

void GameTime::updateTotalTime()
{
	totalTime += deltaTime;
	unscaledTotalTime += deltaTime * timeScale;
}
