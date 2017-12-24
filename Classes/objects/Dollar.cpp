#include "Dollar.h"
#include "Definitions.h"

USING_NS_CC;

Dollar::Dollar()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

cocos2d::Sprite* Dollar::spawnDollar(cocos2d::Layer *layer, unsigned int level)
{
    /* Create dollar sprite */
    auto dollar = Sprite::create("Dollar.png");

    auto dollarBody = PhysicsBody::createCircle(dollar->getContentSize().width / 2);

    auto random = CCRANDOM_0_1();

    auto topPipePosition = random * (visibleSize.height) + dollar->getContentSize().height / 2;

    dollarBody->setDynamic(false);
    dollarBody->setCollisionBitmask(DOLLAR_COLLISION_BITMASK);
    dollarBody->setContactTestBitmask(true);
    dollar->setPhysicsBody(dollarBody);

    dollar->setPosition(Point(visibleSize.width + dollar->getContentSize().width, topPipePosition));
    
    layer->addChild(dollar);

    auto dollarMoveAction = MoveBy::create(DOLLAR_MOVEMENT_SPEED * visibleSize.width - level, Point(-visibleSize.width * 2.5, 0));
    dollar->runAction(dollarMoveAction);

    // TODO(m-peko): Rotate sprite for 360 degrees

    return dollar;
}