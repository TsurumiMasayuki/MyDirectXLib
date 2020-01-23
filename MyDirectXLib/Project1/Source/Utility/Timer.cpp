#include "Timer.h"
#include <cmath>
#include "Device\GameTime.h"

Timer::Timer()
{
}

Timer::Timer(float maxTime)
	: mMaxTime(maxTime), mCurrentTime(0.0f)
{
}

Timer::~Timer()
{
}

void Timer::update()
{
	mCurrentTime += GameTime::getDeltaTime();
}

void Timer::setMaxTime(float value)
{
	mMaxTime = value;
}

void Timer::reset()
{
	mCurrentTime = 0.0f;
}

float Timer::getCurrentTime()
{
	return mCurrentTime;
}

float Timer::getMaxTime()
{
	return mMaxTime;
}

float Timer::getRatio()
{
	return mCurrentTime / mMaxTime;
}

float Timer::getRatioClamped()
{
	return std::fminf(getRatio(), 1.0f);
}

bool Timer::isTime()
{
	return mCurrentTime >= mMaxTime;
}
