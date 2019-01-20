#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MainMenuLayer :public Layer
{
public:
	bool init();
	void onPlay(Object* pSender);
	void onCredit(Object* pSender);
	void onSetting(Object* pSender);
	void onSound(Object* pSender);
	CREATE_FUNC(MainMenuLayer);
};