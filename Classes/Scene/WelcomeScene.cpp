
#include "WelcomeScene.h"
//#include "SaveMapScene.h"
#include "FightGroundScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
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
 
    if ( !Scene::init() )
    {
        return false;
    }

	/* 设置背景音乐 */
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("Soulknightbgm.mp3", true);
	}
    isMusicPlaying = true;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* 音乐控制按钮 */
	auto offMusic = MenuItemImage::create("MusicSelected.png", "MusicSelected.png");
	auto onMusic = MenuItemImage::create("MusicNormal.png", "MusicNormal.png");
    //add
    offMusic->setScale(0.5);
    onMusic->setScale(0.5);
    
	MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Welcome::menuCloseMusic, this),
		onMusic, offMusic, NULL
	);
	musicItem->setPosition(Vec2(130, visibleSize.height / 2-300));

	/* 进入游戏按钮 */
	auto startItem = MenuItemImage::create("NewGameIcon.png", "NewGameIcon.png", CC_CALLBACK_1(Welcome::menuStartCallBack, this));
	startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 - 120));
    //add
    startItem->setScale(0.5);
    
	/* 菜单 */
    auto menu = Menu::create(musicItem,startItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	
    auto sprite = Sprite::create("CoverSelected.png");
    //add
    auto scaleX = visibleSize.width / sprite->getContentSize().width;
    auto scaleY = visibleSize.height / sprite->getContentSize().height;
    auto realScale = scaleX > scaleY ? scaleX : scaleY;
    sprite->setScale(realScale);
    
    if (sprite == nullptr)
    {
        problemLoading("CoverSelected.png");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    }
    return true;
}


void Welcome::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void Welcome::menuStartCallBack(Ref* pSender)
{
	auto nextScene = FightGround::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

void Welcome::menuCloseMusic(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (isMusicPlaying == true) {
		audio->pauseBackgroundMusic();
        isMusicPlaying = false;
	}
	else {
		audio->resumeBackgroundMusic();
        isMusicPlaying = true;
	}
}
