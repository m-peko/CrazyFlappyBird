#include "GameScene.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "utils/AudioManager.h"

USING_NS_CC;

Scene* Game::createScene()
{
    auto scene = Scene::createWithPhysics();
    /* Used only for debugging. Draws red lines around sprites  */
    // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = Game::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bird = new Bird(this);
    score = 0;
    level = 1;
    
    /* Create background sprite */
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    __String *scoreStr = __String::createWithFormat("Score: %i", score);

    /* Create a score label in top right corner of the screen */
    scoreLabel = Label::createWithTTF(scoreStr->getCString(), "fonts/TelemarinesBold.ttf", 30);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width - scoreLabel->getContentSize().width - 100, visibleSize.height - scoreLabel->getContentSize().height));

    this->addChild(scoreLabel, 10000);

    /* Schedule creating pipes */
    this->schedule(schedule_selector(Game::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    /* Schedule creating dollars */
    this->schedule(schedule_selector(Game::spawnDollar), DOLLAR_SPAWN_FREQUENCY * visibleSize.width);

    /* Create a physics contact event listener (in order to detect collision) */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    /* Create a keyboard event listener  */
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* This is same as schedule() but selector is automatically set to Game::update() */
    this->scheduleUpdate();

    /* Show initial level */
    showLevel(level);

    return true;
}

void Game::spawnPipe(float displayTime)
{
    pipe.spawnPipe(this, level);
}

void Game::spawnDollar(float displayTime)
{
    tmpDollar = dollar.spawnDollar(this, level);
}

bool Game::onContactBegin(cocos2d::PhysicsContact &contact)
{
    static unsigned int pointPassed = 0;

    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) ||
        (b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK))
    {
        /* Bird has touched one of the pipes or the edges of the screen - GAME OVER */
        auto scene = GameOver::createScene(score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene, Color3B(40, 47, 60)));

        AudioManager::playSoundEffect("sounds/smash.mp3", 0.5);

        /* Shapes collide */
        return true;
    }
    else if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == POINT_COLLISION_BITMASK) ||
             (b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == POINT_COLLISION_BITMASK))
    {
        /* Increase the score */
        score += POINT_PASS_SCORE;
        pointPassed++;

        /* If user has passed 2th obstacle, increase game level */
        if (pointPassed % 2 == 0)
        {
            level++;
            showLevel(level);
        }

        /* Update score label */
        auto scoreStr = __String::createWithFormat("Score: %i", score);
        scoreLabel->setString(scoreStr->getCString());

        AudioManager::playSoundEffect("sounds/point.mp3", 0.5);

        /* Shapes do not collide */
        return false;
    }
    else if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == DOLLAR_COLLISION_BITMASK) ||
             (b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == DOLLAR_COLLISION_BITMASK))
    {
        /* Increase the score */
        score += DOLLAR_SCORE;

        /* Update score label */
        auto scoreStr = __String::createWithFormat("Score: %i", score);
        scoreLabel->setString(scoreStr->getCString());

        AudioManager::playSoundEffect("sounds/dollar.mp3", 0.5);

        /* Remove dollar */
        this->removeChild(tmpDollar, true);

        /* Shapes do not collide */
        return false;
    }
}

bool Game::onKeyBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        bird->raise();
        this->scheduleOnce(schedule_selector(Game::birdFall), BIRD_FLY_DURATION);
    }

    return true;
}

void Game::birdFall(float dt)
{
    bird->fall();
}

void Game::update(float dt)
{
    bird->fly();
}

void Game::showLevel(int level)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* Create level label */
    auto levelLabel = Label::createWithTTF("LEVEL " + std::to_string(level), "fonts/TelemarinesBold.ttf", 50);
    levelLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + levelLabel->getContentSize().height));

    this->addChild(levelLabel, 10000);

    /* Create fading actions */
    auto fadeIn = FadeIn::create(1.0f);
    auto fadeOut = FadeOut::create(1.0f);

    /* Make sequence out of previous actions */
    auto sequence = Sequence::create(fadeIn, fadeOut, nullptr);

    levelLabel->runAction(sequence);
}