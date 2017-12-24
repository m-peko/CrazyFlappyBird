#ifndef __DOLLAR_H__
#define __DOLLAR_H__

#include "cocos2d.h"

class Dollar
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

public:
    Dollar();

    cocos2d::Sprite* spawnDollar(cocos2d::Layer *layer, unsigned int level);
};

#endif // __DOLLAR_H__
