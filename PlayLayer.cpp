//
//  PlayerLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "PlayLayer.h"
#include "Box.h"
#include "Bullet.h"
#include <cstdlib>
USING_NS_CC;
PlayLayer::PlayLayer()
{
}

PlayLayer::~PlayLayer()
{
}
Scene* PlayLayer::createScene() {
	auto scene = Scene::createWithPhysics();
	auto layer = PlayLayer::create();
	scene->addChild(layer);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	
	//scene->getPhysicsBody()->setContactTestBitmask(0xff);
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());
	
	return scene;
}
bool PlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
	//Scene * scene = Director::getInstance()->getRunningScene();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
    auto menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width-back->getContentSize().width, visibleSize.height-back->getContentSize().height);
    this->addChild(menu);
	initBackground();
	spawBoxes();
	GameItem* bullet = new Bullet(this, Vec2(350, 50));
	map.insert(bullet->itemBody, bullet);
	
	

	gun = Sprite::create();
	gun->setContentSize(Size(BALL_SIZE, BALL_SIZE));
	PhysicsBody* gunBody= PhysicsBody::createCircle(gun->getContentSize().height / 2);
	gunBody->setDynamic(false);
	gunBody->setRotationEnable(false);
	gunBody->setTag(BG_TAG);
	gunBody->setContactTestBitmask(GUN_CONTACTTEST_BITMASK);
	gunBody->setCategoryBitmask(GUN_CATEGORY_BITMASK);
	gunBody->setCollisionBitmask(GUN_COLLISION_BITMASK);
	gun->setPhysicsBody(gunBody);
	gun->setPosition(Vec2(bg->getPosition().x, 
					bg->getPosition().y-bg->getContentSize().height/2 + gun->getContentSize().height/2+10));
	
	this->addChild(gun);



	



	//event, action listenner
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto contactListner = EventListenerPhysicsContact::create();
	contactListner->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
	contactListner->onContactSeparate= CC_CALLBACK_1(PlayLayer::onContactSeparate, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListner, this);
    return true;
}

void PlayLayer::initBackground() {
	bg = Sprite::create();
	bg->setContentSize(Size(BOX_SIZE*ROW_ITEM_COUNT,BOX_SIZE*COLUNM_ITEM_COUNT));
	PhysicsBody* bgBody = PhysicsBody::createEdgeBox(bg->getContentSize());
	bgBody->setDynamic(false);
	bgBody->setRotationEnable(false);
	bgBody->setContactTestBitmask(BG_CONTACTTEST_BITMASK);
	bgBody->setCategoryBitmask(BG_CATEGORY_BITMASK);
	bgBody->setCollisionBitmask(BG_COLLISION_BITMASK);
	bgBody->setTag(BG_TAG);
	bg->setPhysicsBody(bgBody);
	bg->setPosition(10 + bg->getContentSize().width / 2, 20 + bg->getContentSize().height / 2);
	this->addChild(bg);
}
void PlayLayer::spawBoxes() {
	Vec2 bgTopConnerLeftPos = Vec2(bg->getPosition().x-bg->getContentSize().width/2+BOX_SIZE/2, bg->getPosition().y+bg->getContentSize().height/2+BOX_SIZE);
	log("%f %f", bgTopConnerLeftPos.x, bgTopConnerLeftPos.y);
	for (int i = 0; i < ROW_ITEM_COUNT; i++) {

	}

	GameItem* box = new Box(this, bgTopConnerLeftPos, 10);
	map.insert(box->itemBody, box);
	
}

void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}

bool PlayLayer::onTouchBegan(Touch* touch, Event* event) {
	log("touched");
	return true;
}
void PlayLayer::onTouchMoved(Touch* touch, Event* event) {
	log("touch moving");
}
void PlayLayer::onTouchEnded(Touch* touch, Event* event) {
	touch->getLocation();
	//shot();
	log("touch ended");
}
bool PlayLayer::onContactBegin(const PhysicsContact& contact) {

	//log("contact begin");

	//if (contact.getShapeA()->getBody()->getTag() != BG_TAG) map.at(contact.getShapeA()->getBody())->onTouch(this);
	//if (contact.getShapeB()->getBody()->getTag() != BG_TAG) map.at(contact.getShapeB()->getBody())->onTouch(this);
	if (contact.getShapeA()->getBody()->getTag() == BG_TAG || contact.getShapeB()->getBody()->getTag() == BG_TAG) {

		Bullet* bullet;
		if (contact.getShapeA()->getBody()->getTag() == BALL_TAG) bullet = (Bullet*)map.at(contact.getShapeA()->getBody());
		if (contact.getShapeB()->getBody()->getTag() == BALL_TAG) bullet = (Bullet*)map.at(contact.getShapeB()->getBody());
		if (bullet->itemBody->getPosition().y <= gun->getPhysicsBody()->getPosition().y)
		{
			log("bullet in end ");
			bullet->stop();
			/*			Action* moveToGunAction = Sequence::create(
							DelayTime::create(1),
							MoveTo::create(1.0, gun->getPosition()),
							NULL);
						bullet->item->runAction(moveToGunAction);*/
			return true;
		}
	}
	return true;
}
void PlayLayer::onContactSeparate(const PhysicsContact& contact) {
	
	
	log("bullet not in end ");
	if (contact.getShapeA()->getBody()->getTag()& ITEM_TAG) map.at(contact.getShapeA()->getBody())->onTouch(this);
	if (contact.getShapeB()->getBody()->getTag()& ITEM_TAG) map.at(contact.getShapeB()->getBody())->onTouch(this);

}

void shot() {

}