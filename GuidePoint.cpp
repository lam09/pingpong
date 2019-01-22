#include "GuidePoint.h"
GuidePoint::GuidePoint(Layer* layer,Vec2 position):GameItem(layer,position)
{
	item = Sprite::create();
	item->setContentSize(Size(3,3));
	item->setPosition(position);
	PhysicsShape* circleShape = PhysicsShapeCircle::create(item->getContentSize().height / 2, BULLET_MATERIAL);
	circleShape->setMoment(0);
	itemBody = PhysicsBody::create();
	itemBody->addShape(circleShape);
	itemBody->setDynamic(true);
	itemBody->setRotationEnable(false);
	itemBody->setTag(0);
	itemBody->setContactTestBitmask(GUIDE_BALL_CONTACTTEST_BITMASK);
	itemBody->setCategoryBitmask(GUIDE_BALL_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(GUIDE_BALL_COLLISION_BITMASK);
	item->setPhysicsBody(itemBody);
	layer->addChild(item);
}
GuidePoint::~GuidePoint() {

}
void GuidePoint::showLine(Vec2 orientation) {
	GuidePoint *point = this;
	auto go = CallFunc::create([point, orientation]()
	{
		float speed = orientation.x*orientation.x + orientation.y*orientation.y;
		float scale =(sqrt( (BALL_VELOCITY * BALL_VELOCITY) / speed))*2;
		Vec2 vel = Vec2(orientation.x*scale, orientation.y*scale);
		point->itemBody->setVelocity(vel);
	});
	auto deadth = CallFunc::create([point]()
	{
		point->item->getParent()->removeChild(point->item);
	});
	Action* runAndRemove = Sequence::create(
		go,
		DelayTime::create(GUIDE_BALL_LENGTH),
		deadth,
		NULL
	);
	item->runAction(runAndRemove);
}