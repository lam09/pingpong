#include "MainMenuLayer.h"
#include "SceneManager.h"
bool MainMenuLayer::init() {

	if (!Layer::init())return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float delayTime = 0.3f;

	TTFConfig config_font96("Marker Felt.ttf", 96);
	TTFConfig config_font52("Marker Felt.ttf", 52);

/*	Label *titleLeft = Label::createWithTTF(config_font96, "Menu ");
	Label *titleRight = Label::createWithTTF(config_font96, " System");
	Label *titleQuotes = Label::createWithTTF(config_font96, "\"                        \"");
	Label *titleCenterTop = Label::createWithTTF(config_font52, "How to build a...");
	Label *titleCenterBottom = Label::createWithTTF(config_font96, "Part 1");
	*/
	Label *titleGameName = Label::createWithTTF(config_font96, "PING PONG");

	MenuItemFont *startNew = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuLayer::onPlay, this));
	MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MainMenuLayer::onCredit, this));

	Menu *menu = Menu::create(startNew, credits, NULL);

	titleGameName->setPosition(
		Point((visibleSize.width - titleGameName->getContentSize().width) / 2,
			visibleSize.height - 100));
	this->addChild(titleGameName);

/*	titleCenterTop->setPosition(
		Point((visibleSize.width - titleCenterTop->getContentSize().width) / 2,
			visibleSize.height - 100));
	this->addChild(titleCenterTop);

	titleQuotes->setPosition(
		Point((visibleSize.width - titleQuotes->getContentSize().width) / 2,
			titleCenterTop->getPosition().y - titleQuotes->getContentSize().height - 40));
	this->addChild(titleQuotes);
	*/
	


	int tileWidth = titleGameName->getContentSize().width + titleGameName->getContentSize().width + 50;
	/*auto titleLeftPosBegin = Point((visibleSize.width - tileWidth) / 2,
		titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40 - 400);
	auto titleLeftPosEnd = Point((visibleSize.width - tileWidth) / 2,
		titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40);
	auto titleRightPosBegin = Point((visibleSize.width - tileWidth) / 2 + titleLeft->getContentSize().width + 50,
		titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40 + 400);
	auto titleRightPosEnd = Point((visibleSize.width - tileWidth) / 2 + titleLeft->getContentSize().width + 50,
		titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40);
	*/
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
	//this->addChild(titleGameName);

	/*titleRight->setPosition(titleRightPosBegin);
	Action *titleRightAction = Sequence::create(
		DelayTime::create(delayTime),
		EaseBackOut::create(MoveTo::create(1.0, titleRightPosEnd)),
		NULL);
	titleRight->runAction(titleRightAction);
	this->addChild(titleRight);
	titleCenterBottom->setPosition(
		Point((visibleSize.width - titleCenterBottom->getContentSize().width) / 2,
			titleRightPosEnd.y - titleCenterBottom->getContentSize().height - 40));
	this->addChild(titleCenterBottom);
	*/
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