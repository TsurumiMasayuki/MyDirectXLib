#pragma once
class Circle2D;
class Box2D;

class IShape2D
{
public:
	virtual ~IShape2D() {};
	
	//ŽlŠpŒ`‚Æ‚Ì“–‚½‚è”»’è
	virtual bool isIntersect(const Box2D& box2D) const = 0;
	//‰~‚Æ‚Ì“–‚½‚è”»’è
	virtual bool isIntersect(const Circle2D& circle2D) const = 0;

protected:
	IShape2D() {};
};