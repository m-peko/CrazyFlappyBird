#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "objects/Pipe.h"
#include "objects/Dollar.h"
#include "objects/Bird.h"

class Game : public cocos2d::Layer
{
private:
    cocos2d::PhysicsWorld *sceneWorld;
    Pipe pipe;
    Dollar dollar;
    Bird *bird;
    unsigned int score;
    unsigned int level;
    cocos2d::Label *scoreLabel;
    cocos2d::Sprite *tmpDollar;

    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    void spawnPipe(float displayTime);
    void spawnDollar(float displayTime);
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
