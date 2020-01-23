#pragma once

class Timer
{
public:
	Timer();
	Timer(float maxTime);
	~Timer();

	void update();
	void setMaxTime(float value);
	void reset();

	float getCurrentTime();
	float getMaxTime();

	float getRatio();
	float getRatioClamped();

	bool isTime();

private:
	float mCurrentTime;
	float mMaxTime;
};

