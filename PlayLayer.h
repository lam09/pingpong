//
//  PlayerLayer.h
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#ifndef __MenuTutorial__PlayerLayer__
#define __MenuTutorial__PlayerLayer__

#include "cocos2d.h"
#include "SceneManager.h"
#include "Config.h"
#include "GameItem.h"
USING_NS_CC;

class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
	static Scene* createScene();
    virtual bool init();
    void back(Object* pSender);
	void initBackground();
	void spawBoxes();
	void shot();

	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event* event);
	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);

	bool onContactBegin(const PhysicsContact& contact);
	void onContactSeparate(const PhysicsContact& contact);
	
    CREATE_FUNC(PlayLayer);

	Map< PhysicsBody*, GameItem*> map;
	Scene* scene;
	Sprite* gun;
	Sprite* bg;
	bool canShot = true;
	Vec2 gunOrientation= Vec2(50, 50);
	
};

#endif //* defined(__MenuTutorial__PlayerLayer__) */
