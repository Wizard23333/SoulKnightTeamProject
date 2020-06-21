#include "PauseScene.h"
#include "FightGroundScene.h"
USING_NS_CC;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize =  Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //创建返回按钮
    auto closeItem = MenuItemImage::create(
                                           "return.png",
                                           "return.png",
                                           CC_CALLBACK_1(PauseScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 - 100;
        closeItem->setPosition(Vec2(x,y));
    }
    closeItem->setScale(2);
    
    //创建目录
    auto menu = Menu::create(closeItem, NULL);
    
    //创建继续按钮
    auto resumeItem = MenuItemImage::create("continue.png","continue.png",CC_CALLBACK_1(PauseScene::backGameCallback, this));
    resumeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 + 200));
    resumeItem->setScale(2);
    
    //添加到场景中
    menu->addChild(resumeItem, 2);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    return true;
}

void PauseScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(Welcome::createScene());
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void PauseScene::backGameCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}
