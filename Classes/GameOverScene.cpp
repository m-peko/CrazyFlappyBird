#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

unsigned int finalScore;

Scene* GameOver::createScene(unsigned int score)
{
	finalScore = score;
	return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
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

	/* Create 'Game Over' sprite */
	auto gameOverSprite = Sprite::create("GameOver.png");
	gameOverSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + gameOverSprite->getContentSize().height));

	this->addChild(gameOverSprite);

	UserDefault *userDef = UserDefault::getInstance();
	auto highScore = userDef->getIntegerForKey("HIGH_SCORE", 0);

	/* Create label with final score */
	__String *finalScoreStr = __String::createWithFormat("Final score: %i", finalScore);
	auto finalScoreLabel = Label::createWithTTF(finalScoreStr->getCString(), "fonts/TelemarinesBold.ttf", 35);
	finalScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + finalScoreLabel->getContentSize().height));

	this->addChild(finalScoreLabel);

	/* Create label with high score */
	__String *highScoreStr;
	if (highScore < finalScore)
	{
		/* New score is the highest score so far */
		highScore = finalScore;
		userDef->setIntegerForKey("HIGH_SCORE", highScore);
		highScoreStr = __String::createWithFormat("New high score: %i", highScore);
	}
	else
	{
		/* High score remains the same */
		highScoreStr = __String::createWithFormat("High score: %i", highScore);
	}

	auto highScoreLabel = Label::createWithTTF(highScoreStr->getCString(), "fonts/TelemarinesBold.ttf", 35);
	highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - finalScoreLabel->getContentSize().height));

	this->addChild(highScoreLabel);

	/* Create Retry menu item */
	auto retryItem = MenuItemImage::create("RetryButton.png", "RetryButtonClicked.png", CC_CALLBACK_0(GameOver::goToGame, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x - retryItem->getContentSize().width * 0.65, visibleSize.height / 2 + origin.y - (finalScoreLabel->getContentSize().height + highScoreLabel->getContentSize().height) * 1.6));

	/* Create Main Menu menu item */
	auto mainMenuItem = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonClicked.png", CC_CALLBACK_0(GameOver::goToMainMenu, this));
	mainMenuItem->setPosition(Point(visibleSize.width / 2 + origin.x + mainMenuItem->getContentSize().width * 0.65, visibleSize.height / 2 + origin.y - (finalScoreLabel->getContentSize().height + highScoreLabel->getContentSize().height) * 1.6));

	/* Create Menu */
	auto menu = Menu::create(retryItem, mainMenuItem, nullptr);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	return true;
}

void GameOver::goToGame()
{
	auto scene = Game::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene, Color3B(40, 47, 60)));
}

void GameOver::goToMainMenu()
{
	auto scene = MainMenu::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene, Color3B(40, 47, 60)));
}