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
	void goDown();
	void goToRest();
	virtual void onTouch(Layer* layer1);
	//CREATE_FUNC(Box);
};

