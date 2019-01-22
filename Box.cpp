#include "Box.h"
#include <string>


Box::Box(Layer* layer,Vec2 position,int point):GameItem(layer,position)
{
	item = Sprite::create();
	item->setContentSize(Size(BOX_SIZE, BOX_SIZE));
	item->setAnchorPoint(Vec2(0, 0));
	item->setPosition(Vec2(position.x, position.y));
	itemBody = PhysicsBody::createBox(item->getContentSize(),BG_MATERIAL);
	itemBody->setDynamic(false);
	itemBody->setRotationEnable(false);
	itemBody->setTag(BOX_TAG);
	itemBody->setCategoryBitmask(BOX_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(BOX_COLLISION_BITMASK);
	itemBody->setContactTestBitmask(BOX_CONTACTTEST_BITMASK);
	itemBody->setRotationEnable(false);
	item->setPhysicsBody(itemBody);
	itemBody->setPositionOffset(Vec2::ZERO);

	layer->addChild(item);

	count = point;
	TTFConfig config_font("Marker Felt.ttf", BOX_SIZE/2);
	numLabel = Label::createWithTTF(config_font, std::to_string(count));
	numLabel->setPosition(item->getPosition().x+ BOX_SIZE/2, item->getPosition().y+ BOX_SIZE/2);
	layer->addChild(numLabel);
}


Box::~Box()
{
}

void Box::onTouch(Layer* layer)
{
	log("box is hitted");
	count--;
	if (count == 0) {
		layer->removeChild(item);
		layer->removeChild(numLabel);
		return;
	}
	int i = rand() % 6;
	numLabel->setString(std::to_string(count));
	numLabel->setTextColor(colors[i]);
}
void Box::goDown() {	
		Vec2 currentItemPos = item->getPosition();
		itemBody->setPositionOffset(Vec2(0, 0));
		Action* moveBoxDownAction = Sequence::create(
			DelayTime::create(1),
			MoveTo::create(1.0, Vec2(currentItemPos.x, currentItemPos.y - BOX_SIZE)),
			NULL);
		item->runAction(moveBoxDownAction);
		Action* moveLabelDownAction = Sequence::create(
			DelayTime::create(1),
			MoveTo::create(1.0, Vec2(numLabel->getPosition().x, numLabel->getPosition().y - BOX_SIZE)),
			NULL);
		numLabel->runAction(moveLabelDownAction);
}
void Box::goToRest() {

}