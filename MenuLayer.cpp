//
//  MenuLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "MenuLayer.h"
#include "SceneManager.h"
#include "GameConfiguration.h"
USING_NS_CC;

bool MenuLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
	//Director::getInstance()->setClearColor(Color4F::WHITE);
	//setColor(Color3B::WHITE);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float delayTime = 0.3f;
    
    TTFConfig config_font96("Marker Felt.ttf", 96);
    TTFConfig config_font52("Marker Felt.ttf", 52);
    
    Label *titleLeft = Label::createWithTTF(config_font96, "Menu ");
	titleLeft->setColor(Color3B::BLACK);
    Label *titleRight = Label::createWithTTF(config_font96, " System");
    Label *titleQuotes = Label::createWithTTF(config_font96, "\"                        \"");
    Label *titleCenterTop = Label::createWithTTF(config_font52, "How to build a...");
    Label *titleCenterBottom = Label::createWithTTF(config_font96, "Part 1");
    
    MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(MenuLayer::onNewGame, this));
    MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MenuLayer::onCredits, this));

    Menu *menu = Menu::create(startNew, credits, NULL);
    
    titleCenterTop->setPosition(
                    Point( (visibleSize.width - titleCenterTop->getContentSize().width)/2,
                            visibleSize.height - 100) );
    this->addChild(titleCenterTop);
    
    titleQuotes->setPosition(
                    Point((visibleSize.width - titleQuotes->getContentSize().width)/2,
                          titleCenterTop->getPosition().y - titleQuotes->getContentSize().height - 40) );
    this->addChild(titleQuotes);
    
    int tileWidth = titleLeft->getContentSize().width + titleRight->getContentSize().width + 50;
    auto titleLeftPosBegin = Point((visibleSize.width - tileWidth)/2,
                titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40 - 400);
    auto titleLeftPosEnd = Point((visibleSize.width - tileWidth)/2,
                titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40 );
    auto titleRightPosBegin = Point((visibleSize.width - tileWidth)/2+titleLeft->getContentSize().width + 50,
                titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40 + 400);
    auto titleRightPosEnd = Point((visibleSize.width - tileWidth)/2+titleLeft->getContentSize().width + 50,
                titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40);
    
    titleLeft->setPosition(titleLeftPosBegin);
    Action *titleLeftAction = Sequence::create(
                            DelayTime::create(delayTime),
                            EaseBackOut::create(MoveTo::create(1.0, titleLeftPosEnd)),
                            NULL);
    titleLeft->runAction(titleLeftAction);
    this->addChild(titleLeft);
    
    titleRight->setPosition(titleRightPosBegin);
    Action *titleRightAction = Sequence::create(
                            DelayTime::create(delayTime),
                            EaseBackOut::create(MoveTo::create(1.0, titleRightPosEnd)),
                            NULL);
    titleRight->runAction(titleRightAction);
    this->addChild(titleRight);

    
    
    titleCenterBottom->setPosition(
                    Point( (visibleSize.width - titleCenterBottom->getContentSize().width)/2,
                            titleRightPosEnd.y - titleCenterBottom->getContentSize().height - 40) );
    this->addChild(titleCenterBottom);

    menu->setPosition(
            Point( visibleSize.width / 2,
                  titleCenterBottom->getPosition().y-150 ) );
    menu->alignItemsVerticallyWithPadding(80.0f);
   for (Node *each : menu->getChildren())
    {
		each->setScale(0.0f, 0.0f);
		Action *action = Sequence::create(DelayTime::create(delayTime),
                                          ScaleTo::create(0.5f, 1.0f),
                                          NULL);
		delayTime += 0.2f;
		each->runAction(action);
	}
    this->addChild(menu, 2);
	//GameConfiguration::setSound(true);
	
	auto soundBtn = Sprite::create("sound_enabled");
	auto touchListenner = EventListenerTouchOneByOne::create();
	touchListenner->onTouchBegan = [=](Touch*touch,Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			//GameConfiguration::sound_enabled = !GameConfiguration::sound_enabled;
			soundBtn->setTexture("sound_disabled");
		}
		return true;
	};

    return true;
}

void MenuLayer::onNewGame(Object* pSender)
{
    SceneManager::goPlay();
}

void MenuLayer::onCredits(Object* pSender)
{
    SceneManager::goCredit();
}
