#include "MainMenuLayer.h"
#include "SceneManager.h"
bool MainMenuLayer::init() {

	if (!LayerColor::initWithColor(Color4B::WHITE))return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float delayTime = 0.3f;

	TTFConfig config_font96("Marker Felt.ttf", 96);
	TTFConfig config_font52("Marker Felt.ttf", 52);


	Label *titleGameName = Label::createWithTTF(config_font96, "PING PONG");
	titleGameName->setColor(Color3B::BLACK);
	MenuItemFont *startNew = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuLayer::onPlay, this));
	MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MainMenuLayer::onCredit, this));
	startNew->setColor(Color3B::BLACK);
	credits->setColor(Color3B::BLACK);
	Menu *menu = Menu::create(startNew, credits, NULL);

	titleGameName->setPosition(
		Point((visibleSize.width - titleGameName->getContentSize().width) / 2,
			visibleSize.height - 100));
	this->addChild(titleGameName);




	int tileWidth = titleGameName->getContentSize().width + titleGameName->getContentSize().width + 50;
	auto titleGameNamePosBegin = Point((visibleSize.width - tileWidth) / 2 + titleGameName->getContentSize().width + 50,
		titleGameName->getPosition().y - titleGameName->getContentSize().height - 40 + 400);
	auto titleGameNamePosEnd = Point((visibleSize.width - tileWidth) / 2 + titleGameName->getContentSize().width + 50,
		titleGameName->getPosition().y - titleGameName->getContentSize().height - 40);



	titleGameName->setPosition(titleGameNamePosBegin);
	Action *titleLeftAction = Sequence::create(
		DelayTime::create(delayTime),
		EaseBackOut::create(MoveTo::create(1.0, titleGameNamePosEnd)),
		NULL);
	titleGameName->runAction(titleLeftAction);
	menu->setPosition(
		Point(visibleSize.width / 2,
			titleGameName->getPosition().y - 650));
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

	auto soundBtn = Sprite::create("sound1.png");
	soundBtn->setContentSize(Size(75, 75));
	soundBtn->setPosition(Vec2(visibleSize.width - soundBtn->getContentSize().width, visibleSize.height - soundBtn->getContentSize().height));
	auto touchListenner = EventListenerTouchOneByOne::create();
	touchListenner->onTouchBegan = [=](Touch*touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			soundBtn->setTexture("sound2.png");
			soundBtn->setContentSize(Size(75, 75));
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenner,soundBtn);
	addChild(soundBtn);

	return true;
}
void MainMenuLayer::onPlay(Object* pSender) {
	SceneManager::goPlay();
}
void MainMenuLayer::onCredit(Object* pSender){
}
void MainMenuLayer::onSetting(Object* pSender){
}
void MainMenuLayer::onSound(Object* pSender){
}