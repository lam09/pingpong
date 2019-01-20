/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -3000.0f));
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	//layer->setPhyWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);
	scene->getPhysicsWorld()->setDebugDrawMask(0xfff);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// Create sprite and add it to the layer
	_ball = Sprite::create("Ball.jpg", Rect(0, 0, 52, 52));
	_ball->setPosition(Point(400, 600));
	auto ballBody = PhysicsBody::createCircle(_ball->getContentSize().width);
	ballBody->setContactTestBitmask(0x1);
	//ballBody->setDynamic(false);
	_ball->setPhysicsBody(ballBody);
	this->addChild(_ball);

	auto ball2 = Sprite::create("Ball.jpg", Rect(0, 0, 52, 52));
	ball2->setPosition(Point(400, 50));
	auto ball2Body = PhysicsBody::createCircle(ball2->getContentSize().width / 2);
	ball2Body->setContactTestBitmask(0x1);
	//ball2Body->setDynamic(false);
	ball2->setPhysicsBody(ball2Body);
	this->addChild(ball2);



	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody); this->addChild(edgeSp); edgeSp->setTag(0);


	//auto Listener=EventListenerPhysicsContactWithGroup::create(100);

	//auto Listener=EventListenerPhysicsContactWithBodies::create(ball2->getPhysicsBody(), _ball->getPhysicsBody());

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	//this->setAccelerometerEnabled(true);

	return true;
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* unused_event)
{
	//Vect gravity(-acc->y * 15, acc->x * 15);
	//m_world->setGravity(gravity);
}

bool HelloWorld::onContactBegin(PhysicsContact &contact)
{



	auto ObjA = contact.getShapeA()->getBody()->getNode();

	auto ObjB = contact.getShapeB()->getBody()->getNode();

	this->removeChild(ObjB, true);

	this->removeChild(ObjA, true);

	return true;
}
