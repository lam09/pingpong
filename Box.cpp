#include "Box.h"
#include <string>


Box::Box(Layer* layer,Vec2 position,int point):GameItem(layer,position)
{
	item = Sprite::create();
	item->setContentSize(Size(BOX_SIZE, BOX_SIZE));
	item->setPosition(position);
	itemBody = PhysicsBody::createBox(item->getContentSize());
	itemBody->setDynamic(false);
	itemBody->setRotationEnable(false);
	itemBody->setTag(BOX_TAG);
	itemBody->setCategoryBitmask(BOX_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(BOX_COLLISION_BITMASK);
	itemBody->setContactTestBitmask(BOX_CONTACTTEST_BITMASK);
	item->setPhysicsBody(itemBody);
	layer->addChild(item);
	
	count = point;
	TTFConfig config_font("Marker Felt.ttf", 52);
	numLabel = Label::createWithTTF(config_font, std::to_string(count));
	numLabel->setPosition(item->getPosition().x , item->getPosition().y);
	layer->addChild(numLabel);
}


Box::~Box()
{
}

void Box::onTouch(Layer* layer)
{
	log("box is hitted");
	count--;
	numLabel->setString(std::to_string(count));
}