#include "Bullet.h"
#include "math/MathUtil.h"


Bullet::Bullet(Layer* layer, Vec2 position):GameItem(layer,position)
{
	item = Sprite::create();
	item->setContentSize(Size(BALL_SIZE, BALL_SIZE));
	item->setPosition(position);
	itemBody = PhysicsBody::createCircle(item->getContentSize().height / 2);
	itemBody->setDynamic(true);
	itemBody->setRotationEnable(false);
	itemBody->setTag(BALL_TAG);
	itemBody->setContactTestBitmask(BALL_CONTACTTEST_BITMASK);
	itemBody->setCategoryBitmask(BALL_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(BALL_COLLISION_BITMASK);
	itemBody->setVelocity(Vec2(300, 300));
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
	log("bullet is running");
	Vec2 velocity = item->getPhysicsBody()->getVelocity();
	if (currentVelocity.x * velocity.x < 0 && currentVelocity.y * velocity.y > 0) {
		velocity.x = -currentVelocity.x;
		velocity.y = currentVelocity.y;
	}
	else if (currentVelocity.x * velocity.x > 0 && currentVelocity.y * velocity.y < 0) {
		velocity.x = currentVelocity.x;
		velocity.y = -currentVelocity.y;
	}

	float speed = velocity.x*velocity.x + velocity.y*velocity.y;
	float scale = sqrt((BALL_VELOCITY * BALL_VELOCITY) / speed);
	velocity.x = velocity.x*scale;
	velocity.y = velocity.y*scale;
	speed = velocity.x*velocity.x + velocity.y*velocity.y;

	item->getPhysicsBody()->setVelocity(velocity);
	currentVelocity = velocity;
}
void Bullet::stop() {
	isRunning = false;
	itemBody->setVelocity(Vec2(0, 0));


}