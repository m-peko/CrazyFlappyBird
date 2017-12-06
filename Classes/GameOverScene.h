#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
private:
    void goToGame();
    void goToMainMenu();

public:
    static cocos2d::Scene* createScene(unsigned int score);
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __GAMEOVER_SCENE_H__
