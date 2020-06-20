
#include "WelcomeScene.h"
//#include "SaveMapScene.h"
#include "FightGroundScene.h"
#include "cocos2d.h"
//#include "SimpleAudioEngine.h"
#include  "C:\Users\Dell\Desktop\cocos2d-x-3.17.2\cocos2d-x-3.17.2\cocos\audio\include\SimpleAudioEngine.h"
//#include"..\cocos\editor-support\cocostudio\SimpleAudioEngine.h"
USING_NS_CC;

Scene* Welcome::createScene()
{
	return Welcome::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Welcome::init()
{

	if (!Scene::init())
	{
		return false;
	}

	/* ÉèÖÃ±³¾°ÒôÀÖ */
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("SoulKnightBgm.mp3", true);
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* ÒôÀÖ¿ØÖÆ°´Å¥ */
	MenuItemImage *offMusic = MenuItemImage::create("MusicSelected.png", "MusicSelected.png");
	MenuItemImage *onMusic = MenuItemImage::create("MusicNormal.png", "MusicNormal.png");
	offMusic->setScale(0.5);
	onMusic->setScale(0.5);

	MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Welcome::menuCloseMusic, this),
		onMusic, offMusic, NULL
	);
	musicItem->setPosition(Vec2(100, visibleSize.height / 2 - 230));

	/* ½øÈëÓÎÏ·°´Å¥ */
	MenuItemImage *startItem = MenuItemImage::create("NewGameIcon.png", "NewGameIcon.png", CC_CALLBACK_1(Welcome::menuStartCallBack, this));
	startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 - 120));
	startItem->setScale(0.5);

	/* ²Ëµ¥ */
	Menu *menu = Menu::create(musicItem, startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* ±³¾°Í¼Æ¬ */
	Sprite *background = Sprite::create("CoverSelected.png");
	auto scaleX = visibleSize.width / background->getContentSize().width;
	auto scaleY = visibleSize.height / background->getContentSize().height;
	auto realScale = scaleX > scaleY ? scaleX : scaleY;
	background->setScale(realScale);

	if (background == nullptr)
	{
		problemLoading("CoverSelected.png");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}
	return true;
}


void Welcome::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void Welcome::menuStartCallBack(Ref* pSender)
{
	//auto nextScene = SaveMap::createScene();
    auto nextScene = FightGround::createScene();
    
	Director::getInstance()->replaceScene(nextScene);
}

void Welcome::menuCloseMusic(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying()) {
		audio->pauseBackgroundMusic();
	}
	else {
		audio->resumeBackgroundMusic();
	}
}
