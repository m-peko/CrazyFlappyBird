#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class Game : public cocos2d::Layer
{
private:
    cocos2d::PhysicsWorld *sceneWorld;
    Pipe pipe;
    Bird *bird;
    unsigned int score;
    cocos2d::Label *scoreLabel;

    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    void spawnPipe(float displayTime);
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onKeyBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void birdFall(float dt);
    void update(float dt);
	void showLevel(int level);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};

#endif // __GAME_SCENE_H__
