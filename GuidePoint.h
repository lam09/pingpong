#pragma once
#include "GameItem.h"
class GuidePoint :public GameItem {
public:
	GuidePoint(Layer* layer, Vec2 position);
	~GuidePoint();
	void showLine(Vec2 orientation);
};