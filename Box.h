#pragma once
#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;
class Box:public Object
{
public:
	Box(Layer* layer, Vec2 position);
	~Box();
	Label* number;
	Sprite* box;
	PhysicsBody* boxBody;
	void onTouch(Layer* layer1);
	//CREATE_FUNC(Box);
};

