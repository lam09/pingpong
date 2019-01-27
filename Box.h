#pragma once
#include "cocos2d.h"
#include "GameItem.h"
#include "Config.h"
USING_NS_CC;
class Box:public GameItem
{
public:
	Box(Layer* layer, Vec2 position,int point);
	~Box();
	
	Label* numLabel;
	int count;
	bool inSpawing = false,isDeadth = false;
	void goDown();
	void goToRest();
	virtual void onTouch(Layer* layer1);
	const Color4B colors[6] = {Color4B::WHITE,Color4B::RED,Color4B::ORANGE,Color4B::RED,Color4B::RED,Color4B::RED };
	//CREATE_FUNC(Box);
};

