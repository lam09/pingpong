#include "Box.h"
#include "MyBodyParser.h"
#include "PlayLayer.h"
#include <string>


Vec2 offsets[6] = { Vec2(-BOX_SIZE / 4,-BOX_SIZE / 4) ,Vec2(-BOX_SIZE / 4,BOX_SIZE / 4) ,Vec2(BOX_SIZE / 4,BOX_SIZE / 4) ,Vec2(BOX_SIZE / 4,-BOX_SIZE / 4),Vec2(0,0),Vec2(0,0) };
Box::Box(Layer* layer,Vec2 position,int point):GameItem(layer,position)
{
	//item = Sprite::create("item_bodies/citron.png");
	item = Sprite::create();
	item->setContentSize(Size(BOX_SIZE, BOX_SIZE));
	item->setAnchorPoint(Vec2(0.5, 0.5));
	item->setPosition(Vec2(position.x, position.y));
	
	int shapeId = rand() % 5 + 1;
	itemBody = MyBodyParser::getInstance()->bodyFormJson(item, std::to_string(shapeId), BG_MATERIAL);
	
	//itemBody = PhysicsBody::createBox(item->getContentSize(),BG_MATERIAL);
	//itemBody = PhysicsBody::createEdgeBox(item->getContentSize(), BG_MATERIAL,BOX_SIZE/2);

	
	itemBody->setRotationEnable(false);
	itemBody->setTag(BOX_TAG);
	itemBody->setCategoryBitmask(BOX_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(BOX_COLLISION_BITMASK);
	itemBody->setContactTestBitmask(BOX_CONTACTTEST_BITMASK);
	if (itemBody != nullptr) {
		log("item body created");
		itemBody->setDynamic(false);
		item->setPhysicsBody(itemBody);

	}
	layer->addChild(item);

	count = point;
	TTFConfig config_font("Marker Felt.ttf", BOX_SIZE/3);
	numLabel = Label::createWithTTF(config_font, std::to_string(count));

	numLabel->setPosition(item->getPosition().x+offsets[shapeId-1].x, item->getPosition().y + offsets[shapeId - 1].y);
	layer->addChild(numLabel);
}


Box::~Box()
{
}

void Box::onTouch(Layer* layer)
{
	log("box is hitted");
	count--;
	if (count < 0)return;
	if (count == 0) {
		goToRest();
		return;
	}
	
	int i = rand() % 6;
	log("current count %d",count);

	numLabel->setString(std::to_string(count));
	numLabel->setTextColor(colors[i]);
}
void Box::goDown() {
	if (item == nullptr) return;
	inSpawing = true;
	Box* b = this;
	CallFunc* callback = CallFunc::create([b]() {
		b->inSpawing = false;
	});
		Vec2 currentItemPos = item->getPosition();
		itemBody->setPositionOffset(Vec2(0, 0));
		Action* moveBoxDownAction = Sequence::create(
			DelayTime::create(0.2),
			MoveTo::create(0.5, Vec2(currentItemPos.x, currentItemPos.y - BOX_SIZE)),
			callback,
			NULL);
		item->runAction(moveBoxDownAction);
		Action* moveLabelDownAction = Sequence::create(
			DelayTime::create(0.2),
			MoveTo::create(0.5, Vec2(numLabel->getPosition().x, numLabel->getPosition().y - BOX_SIZE)),
			NULL);
		numLabel->runAction(moveLabelDownAction);
}
void Box::goToRest() {
	auto explosionEffect = ParticleFireworks::create();
	explosionEffect->setDuration(0.1);
	explosionEffect->setPosition(Vec2(item->getPosition().x + BOX_SIZE / 2, item->getPosition().y - BOX_SIZE / 2));
	item->getParent()->addChild(explosionEffect);
	PlayLayer* layer = (PlayLayer*)item->getParent();
	
	item->getParent()->removeChild(numLabel);
	item->getParent()->removeChild(item);

}