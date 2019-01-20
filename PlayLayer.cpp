//
//  PlayerLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "PlayLayer.h"
#include "Box.h"
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
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());
	return scene;
}
bool PlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
    auto menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width-back->getContentSize().width, visibleSize.height-back->getContentSize().height);
    this->addChild(menu);

	Sprite* bullet = Sprite::create();
	bullet->setContentSize(Size(BALL_SIZE, BALL_SIZE));
	bullet->setPosition(Vec2(350, 25));
	PhysicsBody* bulletBody = PhysicsBody::createCircle(bullet->getContentSize().height/2);
	bulletBody->setDynamic(true);
	bulletBody->setTag(BALL_TAG);
	bullet->setPhysicsBody(bulletBody);
	bulletBody->setVelocity(Vec2(0, 300));
	this->addChild(bullet);
	
	Sprite* bg = Sprite::create();
	bg->setContentSize(Size(BACKGROUND_WIDTH, BACKGROUND_HEIGH));
	PhysicsBody* bgBody = PhysicsBody::createEdgeBox(bg->getContentSize());
	bgBody->setDynamic(false);
	bgBody->setRotationEnable(false);
	bg->setPhysicsBody(bgBody);
	bg->setPosition(10+bg->getContentSize().width/2, 20+bg->getContentSize().height/2);
	this->addChild(bg);

	Box* box = new Box(this,Vec2(150,200));
	map.insert(box->boxBody, box);
//	Box* box1 = new Box(this, Vec2(350, 400));
//	map.insert(box1->boxBody, box1);


	Sprite *b = Sprite::create();
	b->setContentSize(Size(BOX_SIZE, BOX_SIZE));
	b->setPosition(Vec2(350, 400));
	PhysicsBody* boxBody = PhysicsBody::createBox(b->getContentSize());
	boxBody->setDynamic(false);
	boxBody->setRotationEnable(false);
	boxBody->setTag(BOX_TAG);
	b->setPhysicsBody(boxBody);
	this->addChild(b);


	//event, action listenner
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto contactListner = EventListenerPhysicsContact::create();
	contactListner->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListner, this);
//	dispatcher->addEventListenerWithSceneGraphPriority(contactListner, this);
    return true;
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
	log("touch ended");
}
bool PlayLayer::onContactBegin(const cocos2d::PhysicsContact& contact) {
	log("contact begin");
	auto nodeA = (Sprite*)contact.getShapeA()->getBody();
	int tag = nodeA->getTag();
	Box* box;
	if (tag == BOX_TAG) box = map.at(contact.getShapeA()->getBody());
	else box = map.at(contact.getShapeB()->getBody());
	box->onTouch(this);
	return true;
}