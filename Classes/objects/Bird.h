#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite *flappyBird;
    bool isGoingUp;

public:
    Bird(cocos2d::Layer *layer);
    void fly();
    void raise() { isGoingUp = true; };
    void fall() { isGoingUp = false; };
};

#endif // __BIRD_H__
