#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	isGoingUp = false;

	flappyBird = Sprite::create("Bird.png");
	flappyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	/* Minimize sprite a bit */
	flappyBird->setScale(0.5);

	auto flappyBirdBody = PhysicsBody::createCircle(flappyBird->getContentSize().width / 2);
	flappyBirdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBirdBody->setContactTestBitmask(true);
	flappyBird->setPhysicsBody(flappyBirdBody);

	layer->addChild(flappyBird, 100);
}

void Bird::fly()
{
	if (isGoingUp == true)
	{
		/* Increase bird's position on Y axis */
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + BIRD_FLYING_SPEED * visibleSize.height);
	}
	else
	{
		/* Decrease bird's position on Y axis */
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - BIRD_FALLING_SPEED * visibleSize.height);
	}
}