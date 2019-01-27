#include "Bullet.h"
#include "math/MathUtil.h"


Bullet::Bullet(Layer* layer, Vec2 position):GameItem(layer,position)
{
	item = Sprite::create("Ball.png");
	item->setLocalZOrder(2);
	item->setContentSize(Size(BALL_SIZE, BALL_SIZE));
	item->setPosition(position);
//	itemBody=PhysicsBody::createEdgeBox(item->getContentSize(), BULLET_MATERIAL, BALL_SIZE / 2);

	PhysicsShape* circleShape = PhysicsShapeCircle::create(item->getContentSize().height / 2, BULLET_MATERIAL);
	circleShape->setMoment(0);
	itemBody = PhysicsBody::create();
	itemBody->addShape(circleShape);
	itemBody->setMoment(0);
	itemBody->setDynamic(true);
	itemBody->setRotationEnable(false);
	itemBody->setTag(BALL_TAG);
	itemBody->setContactTestBitmask(BALL_CONTACTTEST_BITMASK);
	itemBody->setCategoryBitmask(BALL_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(BALL_COLLISION_BITMASK);
	item->setPhysicsBody(itemBody);
	layer->addChild(item);
	currentVelocity = itemBody->getVelocity();
}


Bullet::~Bullet()
{
}

void Bullet::onTouch(Layer* layer)
{
	if (!isRunning) return;
	Vec2 velocity = item->getPhysicsBody()->getVelocity();
/*	if (currentVelocity.x * velocity.x < 0 && currentVelocity.y * velocity.y > 0) {
		velocity.x = -currentVelocity.x;
		velocity.y = currentVelocity.y;
	}
	else if (currentVelocity.x * velocity.x > 0 && currentVelocity.y * velocity.y < 0) {
		velocity.x = currentVelocity.x;
		velocity.y = -currentVelocity.y;
	}
	*/
/*	float speed = velocity.x*velocity.x + velocity.y*velocity.y;
	float scale = sqrt((BALL_VELOCITY * BALL_VELOCITY) / speed);
	velocity.x = velocity.x*scale;
	velocity.y = velocity.y*scale;
	speed = velocity.x*velocity.x + velocity.y*velocity.y;*/
//	if (abs(velocity.y) < 20)
//		if (velocity.y < 0)velocity.y = -20; else velocity.y = 20;

	item->getPhysicsBody()->setVelocity(velocity);
	currentVelocity = velocity;
}
void Bullet::stop() {
	log("bullet is stopping ");
	isRunning = false;
	itemBody->setVelocity(Vec2(0, 0));
	currentVelocity = Vec2(0, 0);
}
void Bullet::shot(Vec2 velocity) {
	log("bullet is shoting ");
	log("shoting velocity in bullet %f %f", velocity.x, velocity.y);
	itemBody->setVelocity(Vec2(0, 0));
	itemBody->setVelocity(velocity);
	currentVelocity = velocity;
	isRunning = true;
}