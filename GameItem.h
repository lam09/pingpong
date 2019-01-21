#pragma once
#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;
class GameItem :public Object
{
public:
	GameItem(Layer* layer, Vec2 position);
	~GameItem();
	int width;
	int height;
	Label* number;
	Sprite* item;
	PhysicsBody* itemBody;
	virtual void onTouch(Layer* layer1);
};

