#pragma once
#include <string>

class AbstractScene
{
public:
	AbstractScene();
	virtual ~AbstractScene();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void shutdown() = 0;

	virtual std::string nextScene() = 0;
	virtual bool isEnd() = 0;
};

