#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* Create background sprite */
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    /* Create title sprite */
    auto titleSprite = Sprite::create("Title.png");
    titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + titleSprite->getContentSize().height));
    
    this->addChild(titleSprite);

    /* Create Play menu item */
    auto playItem = MenuItemImage::create("PlayButton.png", "PlayButtonClicked.png", CC_CALLBACK_0(MainMenu::goToGame, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    /* Create Menu */
    auto menu = Menu::create(playItem, nullptr);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    /* Create Sound checkbox */
    auto soundCheckBox = ui::CheckBox::create("SoundButton.png", "SoundButtonChecked.png");
    soundCheckBox->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - playItem->getContentSize().height * 1.4));
    
    this->addChild(soundCheckBox);

    soundCheckBox->addEventListener([](Ref *sender, ui::CheckBox::EventType type){
        switch (type)
        {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            cocos2d::experimental::AudioEngine::pauseAll();
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            cocos2d::experimental::AudioEngine::resumeAll();
            break;
        default:
            break;
        }
    });

    return true;
}

void MainMenu::goToGame()
{
    auto scene = Game::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene, Color3B(40, 47, 60)));
}
