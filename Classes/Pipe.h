#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"

class Pipe
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

public:
	Pipe();

	void spawnPipe(cocos2d::Layer *layer);
};

#endif // __PIPE_H__
