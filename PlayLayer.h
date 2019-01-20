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
#include "Box.h"
USING_NS_CC;

class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
	static Scene* createScene();
    virtual bool init();
    void back(Object* pSender);
    
	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event* event);
	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);

	bool onContactBegin(const PhysicsContact& contact);
    CREATE_FUNC(PlayLayer);

	Map< PhysicsBody*, Box*> map;

};

#endif //* defined(__MenuTutorial__PlayerLayer__) */
