#pragma once

class GameTime sealed
{
public:
	static void update();
	static void addSleepTime(float value);

	static float getDeltaTime();
	static float getUnscaledDeltaTime();

	static float getTotalTime();
	static float getUnscaledTotalTime();

private:
	static void updateDeltaTime();
	static void updateTotalTime();

public:
	static float timeScale;

private:
	static float deltaTime;

	static float totalTime;
	static float unscaledTotalTime;

	static long curTime;
	static long preTime;

private:
	GameTime();
	~GameTime() {};
};