#include "Box.h"



Box::Box(Layer* layer,Vec2 position)
{
	box = Sprite::create();
	box->setContentSize(Size(BOX_SIZE, BOX_SIZE));
	box->setPosition(position);
	boxBody = PhysicsBody::createBox(box->getContentSize());
	boxBody->setDynamic(false);
	boxBody->setRotationEnable(false);
	boxBody->setTag(BOX_TAG);
	box->setPhysicsBody(boxBody);
	layer->addChild(box);

}


Box::~Box()
{
}

void Box::onTouch(Layer* layer)
{
	log("box is hitted");
}