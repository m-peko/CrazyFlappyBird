#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::spawnPipe(cocos2d::Layer *layer)
{
	/* Create top and bottom pipe sprites */
	auto topPipe = Sprite::create("Pipe.png");
	auto bottomPipe = Sprite::create("Pipe.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD)
	{
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
	{
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipePosition = random * (visibleSize.height) + topPipe->getContentSize().height / 2;

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width, topPipePosition));
	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height - Sprite::create("Bird.png")->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 2.5, 0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 2.5, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	/* Create 'empty' node in order to conclude that the user has successfully passed the obstacle */
	auto pointNode = Node::create();
	auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("Bird.png")->getContentSize().height));
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2 - Sprite::create("Bird.png")->getContentSize().height / 2));

	layer->addChild(pointNode);

	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 2.5, 0));
	pointNode->runAction(pointNodeAction);
}