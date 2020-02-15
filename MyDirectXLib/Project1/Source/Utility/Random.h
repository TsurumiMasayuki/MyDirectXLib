#pragma once

//ランダム用クラス
class Random
{
public:
	Random();
	~Random();

	int getRandom(int min, int max);
	float getRandom(float min, float max);

private:
	unsigned int m_Seed;
};