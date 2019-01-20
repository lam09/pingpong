#pragma once
#include "cocos2d.h"
USING_NS_CC;
class CustomLayer :public Layer
{
public:
	Scene* createScene() {
		auto scene = Scene::create();
		return scene;
	};
	virtual CustomLayer create();
};