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
#include "GuidePoint.h"
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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -10));
	scene->getPhysicsWorld()->setFixedUpdateRate(60);
	//scene->getPhysicsBody()->setContactTestBitmask(0xff);
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}
bool PlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
	//Scene * scene = Director::getInstance()->getRunningScene();

    visibleSize = Director::getInstance()->getVisibleSize();
	setContentSize(visibleSize);
    

	initBackground();
	//spawBoxes();
	
	initMenu();

	//event, action listenner
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	/*auto initListener = EventListenerCustom::create("game_init", [=](EventCustom *event) {
		initBackground();
		spawBoxes();
		bullet = new Bullet(this, Vec2(350, 50));
		map.insert(bullet->itemBody, bullet);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(initListener, this);
	*/
	auto generateBoxesListener = EventListenerCustom::create("on_generated_boxes", [=](EventCustom *event) {
		log("set spawingInprogress to false");
		spawingInprogress = false;
	});
	dispatcher->addEventListenerWithSceneGraphPriority(generateBoxesListener, this);

	//EventCustom event("game_init");
	//_eventDispatcher->dispatchCustomEvent("game_init");

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto contactListner = EventListenerPhysicsContact::create();
	contactListner->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
	contactListner->onContactPreSolve = CC_CALLBACK_2(PlayLayer::onContactPreSolve, this);
	contactListner->onContactSeparate= CC_CALLBACK_1(PlayLayer::onContactSeparate, this);
	
	dispatcher->addEventListenerWithSceneGraphPriority(contactListner, this);
	//schedule(schedule_selector(PlayLayer::showGuideLine),1);
	this->scheduleUpdate();
	return true;
}

void PlayLayer::update(float dt) {
	Layer::update(dt);
	//log("fucking update");
	if (onShowGuideLine) {
		showGuideLine(currentTouchLoc);
	}
	if (canSpaw && !spawingInprogress) spawBoxes();
}
void PlayLayer::initMenu() {
	auto back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
	auto menu = Menu::create(back, NULL);
	menu->setPosition(visibleSize.width - back->getContentSize().width, visibleSize.height - back->getContentSize().height);
	this->addChild(menu);
}
void PlayLayer::initBackground() {
	Sprite* backgroundImage = Sprite::create("background.png");
	backgroundImage->setContentSize(visibleSize);
	backgroundImage->setAnchorPoint(Vec2(0, 0));
	backgroundImage->setPosition(Vec2(0, 0));
	backgroundImage->setLocalZOrder(1);
	this->addChild(backgroundImage);
	bg = Sprite::create();
	bg->setContentSize(Size(BOX_SIZE*ROW_ITEM_COUNT+2*BACKGROUND_BORDER,BOX_SIZE*COLUNM_ITEM_COUNT+ 3*BACKGROUND_BORDER));
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, -BACKGROUND_BORDER));
	PhysicsBody* bgBody = PhysicsBody::createEdgeBox(bg->getContentSize(), BG_MATERIAL,BACKGROUND_BORDER);
	bgBody->setDynamic(false);
	bgBody->setRotationEnable(false);
	bgBody->setContactTestBitmask(BG_CONTACTTEST_BITMASK);
	bgBody->setCategoryBitmask(BG_CATEGORY_BITMASK);
	bgBody->setCollisionBitmask(BG_COLLISION_BITMASK);
	bgBody->setTag(BG_TAG);
	bg->setPhysicsBody(bgBody);
	
	//bg->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height / 2);
	this->addChild(bg);
	gun = Sprite::create("gun.png");
	gun->setLocalZOrder(3);
	//gun->setContentSize(Size(BALL_SIZE, BALL_SIZE));
	gun->setPosition(Vec2(bg->getPosition().x + bg->getContentSize().width / 2 /*- gun->getContentSize().width / 2*/,
		bg->getPosition().y /* gun->getContentSize().height / 2*/ + BACKGROUND_BORDER));
/*	PhysicsBody* gunBody = PhysicsBody::createCircle(gun->getContentSize().height / 2);
	gunBody->setDynamic(false);
	gunBody->setRotationEnable(false);
	gunBody->setTag(BG_TAG);
	gunBody->setContactTestBitmask(GUN_CONTACTTEST_BITMASK);
	gunBody->setCategoryBitmask(GUN_CATEGORY_BITMASK);
	gunBody->setCollisionBitmask(GUN_COLLISION_BITMASK);
	gun->setPhysicsBody(gunBody);
	*/
	gun->setAnchorPoint(Vec2(0.5,0.17647));
	this->addChild(gun);
	//gun->setRotation(90);
/*	bullet = new Bullet(this, gun->getPosition());
	map.insert(bullet->itemBody, bullet);*/
	Sprite* backgroundBottom = Sprite::create("backgroundBottom.png");
	backgroundBottom->setLocalZOrder(4);
	backgroundBottom->setContentSize(Size(visibleSize.width,BACKGROUND_BORDER+100));
	backgroundBottom->setAnchorPoint(Vec2(0, 0));
	backgroundBottom->setPosition(Vec2(0, -BACKGROUND_BORDER));
	this->addChild(backgroundBottom);
}
void PlayLayer::spawBoxes() {
	//Vec2 bgTopConnerLeftPos = Vec2(BACKGROUND_BORDER/2+bg->getPosition().x-bg->getContentSize().width/2+BOX_SIZE/2, BACKGROUND_BORDER / 2 + bg->getPosition().y+bg->getContentSize().height/2+BOX_SIZE/2);
	spawingInprogress = true; canSpaw = false;
	Vec2 bgTopConnerLeftPos = Vec2(BACKGROUND_BORDER+BOX_SIZE/2,bg->getContentSize().height- BACKGROUND_BORDER/*+BOX_SIZE/2*/);
	log("spawing boxes started %f %f", bgTopConnerLeftPos.x, bgTopConnerLeftPos.y);
	for (int i = 0; i < ROW_ITEM_COUNT; i++) {
		if (rand() % ROW_ITEM_COUNT < 2) {
			GameItem* box = new Box(this, Vec2(bgTopConnerLeftPos.x + i * BOX_SIZE, bgTopConnerLeftPos.y), currentPoint);
			map.insert(box->itemBody, box);
		}
	}

	for (Map< PhysicsBody*, GameItem*>::iterator itr = map.begin(); itr != map.end(); ++itr) {
		GameItem* item = itr->second;
		if (item->itemBody->getTag() == BOX_TAG) {
			Box* box = (Box*)item;
			box->goDown();
		}
	}
	currentPoint++;
	//generate new ball
	bullet = new Bullet(this, gun->getPosition());
	map.insert(bullet->itemBody, bullet);
	CallFunc* cb = CallFunc::create([this]() {
		//EventCustom event("on_generated_boxes");
		spawingInprogress = false;
		log("spawing finish");
		//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("on_generated_boxes");
	});
	Action* cbAction = Sequence::create(
		DelayTime::create(2),
		cb,
		NULL
	);
	this->runAction(cbAction);
}

void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
void PlayLayer::rotateGun() {
	Vec2 rotation = Vec2(currentTouchLoc.x - gun->getPosition().x, currentTouchLoc.y - gun->getPosition().y);
	float degree = (rotation.x*rotation.y>0) ? 90 - atan(rotation.y / rotation.x) * 180 / 3.14 :270- atan(rotation.y / rotation.x) * 180 / 3.14;
	gun->setRotation(degree);
}

bool PlayLayer::onTouchBegan(Touch* touch, Event* event) {
	currentTouchLoc = touch->getLocation();

	rotateGun();
	onShowGuideLine = true;
	return true;
}
void PlayLayer::onTouchMoved(Touch* touch, Event* event) {
	log("touch moving");
	currentTouchLoc = touch->getLocation();
	rotateGun();
}
void PlayLayer::onTouchEnded(Touch* touch, Event* event) {
	onShowGuideLine = false;
	Vec2 touchLocation = touch->getLocation();
	float x1, y1, x2, y2;
	x1 = gun->getPosition().x; y1 = gun->getPosition().y;
	x2 = touchLocation.x; y2 = touchLocation.y;
	Vec2 velocity = Vec2(x2 - x1, y2 - y1);
	if (velocity.y < 20)return;
	//scale velocity
	float speed = velocity.x*velocity.x + velocity.y*velocity.y;
	float scale = sqrt((BALL_VELOCITY * BALL_VELOCITY) / speed);
	velocity.x = velocity.x*scale;
	velocity.y = velocity.y*scale;	
	float length = velocity.x*velocity.x + velocity.y*velocity.y;
	if (isCanShot()) {
		for (Map< PhysicsBody*, GameItem*>::iterator itr = map.begin(); itr != map.end(); ++itr) {
			GameItem* item = itr->second;
			if (item->itemBody->getTag() == BOX_TAG) {
				Box* box = (Box*)item;
				if (box->isDeadth) {
					map.erase(box->itemBody);
					delete box;
				}
			}
		}
		shot(velocity);
	}
		log("touch ended");
}
bool PlayLayer::onContactBegin(const PhysicsContact& contact) {
	log("contact triggered");
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	if ((a->getTag()|b->getTag()) == (BG_TAG|BALL_TAG))// || b->getTag() == BG_TAG) {
	{
		Bullet* bullet;
		if (a->getTag() == BALL_TAG || b->getTag() == BALL_TAG) {
			log("ball hit background");
			if (a->getTag() == BALL_TAG) bullet = (Bullet*)map.at(a);
			if (b->getTag() == BALL_TAG) bullet = (Bullet*)map.at(b);
			if (bullet->itemBody->getPosition().y <= gun->getPosition().y+gun->getContentSize().height/2 && bullet->isRunning)
			{
				bullet->stop();
				if (isCanShot()) {					
					canSpaw = true;
				}
				else canSpaw = false;
				return true;
			}
		}
	}
	return true;
}

bool PlayLayer::onContactPreSolve(PhysicsContact& contact,PhysicsContactPreSolve& solve) {
/*	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	if (contact.getShapeA()->getBody()->getTag() == 0 || contact.getShapeB()->getBody()->getTag() == 0)solve.setRestitution(1);
	if ((a->getTag() == BOX_TAG && b->getTag() == BALL_TAG) || (b->getTag() == BOX_TAG && a->getTag() == BALL_TAG)) solve.setRestitution(1);
	if ((a->getTag() == BG_TAG && b->getTag() == BALL_TAG) || (b->getTag() == BG_TAG && a->getTag() == BALL_TAG)) solve.setRestitution(1);
*/
	return true;
}
int i = 0;
void PlayLayer::onContactSeparate(const PhysicsContact& contact) {
	log("contact %i ended",i);
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	//if (a->getTag() == 0 || b->getTag() == 0)return;
	i++;
	if ((a->getTag() == BOX_TAG && b->getTag() == BALL_TAG) || (b->getTag() == BOX_TAG && a->getTag() == BALL_TAG)){
		map.at(a)->onTouch(this);
		map.at(b)->onTouch(this);
	}
}
bool PlayLayer::isCanShot() {
	if (spawingInprogress) return false;
	for (Map< PhysicsBody*, GameItem*>::iterator itr = map.begin(); itr != map.end(); ++itr) {
		GameItem* item = itr->second;
		if (item->itemBody->getTag() == BALL_TAG) {
			log("found bullet in items map ");
			Bullet* bullet = (Bullet*)item;
			if (bullet->isRunning) {
				canShot = false;
				return false;
			}
		}
	}
	canShot = true;
	return true;
}
void PlayLayer::shot(Vec2 velocity) {
	int i = 1;
	log("shoting velocity in layer %f %f", velocity.x, velocity.y);
	for (Map< PhysicsBody*, GameItem*>::iterator itr = map.begin(); itr != map.end(); ++itr) {
		GameItem* item = itr->second;
		if (item->itemBody->getTag() == BALL_TAG) {
			Bullet* bullet = (Bullet*)item;
			//auto callBack = CallFunc::create(bullet, callfunc_selector(Bullet::shot(velocity)));
			auto callBack = CallFunc::create([bullet,velocity]()
			{
				bullet->shot(velocity);
			});			
			double timeToMove = 0.2;
			double delay = i * 0.1;
			i++;
			Action* moveToGunAndShot = Sequence::create(
				DelayTime::create(0.1),
				MoveTo::create(timeToMove, Vec2(gun->getPosition().x, gun->getPosition().y)),
				DelayTime::create(delay),			
				callBack,
				NULL
			);
			bullet->item->runAction(moveToGunAndShot);
		}
	}
}
void PlayLayer::showGuideLine(Vec2 touchLocation) {
	if (!onShowGuideLine) return;
	//log("showing line %f %f", touchLocation.x, touchLocation.y);

	GuidePoint *point = new GuidePoint(this, gun->getPosition());
	point->showLine(Vec2(touchLocation.x-gun->getPosition().x, touchLocation.y - gun->getPosition().y));
}