#pragma once
#include "cocos2d.h"
#include "Config.h"
#include "GameItem.h"
USING_NS_CC;
class Bullet :public GameItem
{
public:
	Bullet(Layer* layer, Vec2 position);
	~Bullet();
	/*Label* number;
	Sprite* box;
	PhysicsBody* boxBody;*/
	Vec2 currentVelocity;
	virtual void onTouch(Layer* layer1);
	bool isRunning = false;
	void stop();
	void shot(Vec2 velocity);
	//CREATE_FUNC(Box);
};

