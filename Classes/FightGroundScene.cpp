/*
  战斗场景基本组件
 */
#include "FightGroundScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
Scene * FightGround::createScene()
{
    return FightGround::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool FightGround::init()
{
    if(!Scene::init())//场景初始化检测
    {
        return false;
    }
    
    if(!Scene::initWithPhysics())//物理引擎初始化检测
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();//可见范围大小
    auto originPoint = Director::getInstance()->getVisibleOrigin();//原点
    
    auto background = DrawNode::create();//背景
    background->drawSolidRect(originPoint, visibleSize, cocos2d::Color4F::GRAY);
    this->addChild(background, 0);
    
    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(FightGround::menucloseCallBack, this));//退出按钮
    float x = originPoint.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = originPoint.y + visibleSize.height - closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));
    auto menu = Menu::create(closeItem, nullptr);//主菜单
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    myHero.HeroCreate("Ninja.png");//创建英雄
    myHero._sprite->setPosition(Vec2(originPoint.x + 0.5 * visibleSize.width, originPoint.y + 0.5 * visibleSize.height));//设置位置
    this->addChild(myHero._sprite, 1);
    myHero._sprite->setTag(999);//添加Tag值
    
    this->monsterinit();//初始化怪物设置
    
    auto eventListener = EventListenerTouchOneByOne::create();//触摸事件监听
    eventListener->onTouchBegan = CC_CALLBACK_2(FightGround::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();//碰撞事件监听
    contactListener->onContactBegin = CC_CALLBACK_1(FightGround::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    //键盘控制
    auto keyListener = EventListenerKeyboard::create();//键盘事件监听
    keyListener->onKeyPressed = CC_CALLBACK_2(FightGround::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(FightGround::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    return true;
    
    
    
}

void FightGround::menucloseCallBack(Ref* pSender)//关闭按钮的回调
{
     Director::getInstance()->end();
}

bool FightGround::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)//触摸的回调
{
    return true;
}

bool FightGround::onContactBegan(cocos2d::PhysicsContact & contact)//碰撞的回调
{
    myHero.onContactBegin(contact);//成员函数处理碰撞信息
    return true;
}

bool  FightGround::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)//按键按下的回调
{
    myHero.onKeyPressed(keycode);//成员函数处理键盘信息//下同
    return true;
}

bool FightGround::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    myHero.onKeyRelesed(keycode);
    return true;
}

void FightGround::monsterinit()//怪物初始化
{
    
    this->scheduleOnce(schedule_selector(FightGround::addmonster), 0.1f);//在0.1s后添加怪物
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(FightGround::automoveM), 1.0f);//每隔一秒怪物运动
    this->schedule(schedule_selector(FightGround::autoshootM), 1.0f);//每隔一秒怪物射击
    
}

void FightGround::addmonster(float dt)//创建并添加怪物
{
    monster1.monsterCreate(std::string("monster copy.png"), 20, 2);
    monster2.monsterCreate(std::string("monster copy.png"), 20, 2);
    monster3.monsterCreate(std::string("monster copy.png"), 20, 2);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    monster1._sprite->setPosition(visibleSize.width * 0.33, visibleSize.height / 2);
    monster2._sprite->setPosition(visibleSize.width * 0.66, visibleSize.height / 2);
    monster3._sprite->setPosition(visibleSize.width * 0.77, visibleSize.height / 2);
    this->addChild(monster1._sprite, 1);
    this->addChild(monster2._sprite, 1);
    this->addChild(monster3._sprite, 1);

}

void FightGround::automoveM(float dt)
{
    monster1.autoMove();//用类的成员函数控制怪物的运动
    monster2.autoMove();
    monster3.autoMove();
}

void FightGround::autoshootM(float dt)//自动攻击
{
    auto destination = myHero._sprite->getPosition();//获取需要的坐标
    auto originPlace1 = monster1._sprite->getPosition();
    auto originPlace2 = monster2._sprite->getPosition();
    auto originPlace3 = monster3._sprite->getPosition();
    //设置各个方向
    auto direction1 = Vec2(20 * (destination.x - originPlace1.x), 20 * (destination.y - originPlace1.y));
    direction1.normalize();
    auto direction2 = Vec2(20 * (destination.x - originPlace2.x), 20 * (destination.y - originPlace2.y));
    direction2.normalize();
    auto direction3 = Vec2(20 * (destination.x - originPlace3.x), 20 * (destination.y - originPlace3.y));
    direction3.normalize();
    
    //创建各个子弹并设置Tag,位置,添加到场景
    auto bullet1 = cocos2d::Sprite::create("Bullet.png");
    bullet1->setTag(333);
    bullet1->setPosition(originPlace1);
    this->addChild(bullet1, 1);
    
    auto bullet2 = cocos2d::Sprite::create("Bullet.png");
    bullet2->setTag(333);
    bullet2->setPosition(originPlace2);
    this->addChild(bullet2, 1);
    
    auto bullet3 = cocos2d::Sprite::create("Bullet.png");
    bullet3->setTag(333);
    bullet3->setPosition(originPlace3);
    this->addChild(bullet3, 1);
    //设置physicsbody
    auto physicbody1 = cocos2d::PhysicsBody::createBox(bullet1->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody1->setDynamic(false);
    physicbody1->setCategoryBitmask(0x01);
    physicbody1->setContactTestBitmask(0x01);
    bullet1->setPhysicsBody(physicbody1);
    
    auto physicbody2 = cocos2d::PhysicsBody::createBox(bullet2->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody2->setDynamic(false);
    physicbody2->setCategoryBitmask(0x01);
    physicbody2->setContactTestBitmask(0x01);
    bullet2->setPhysicsBody(physicbody2);
    
    auto physicbody3 = cocos2d::PhysicsBody::createBox(bullet3->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody3->setDynamic(false);
    physicbody3->setCategoryBitmask(0x01);
    physicbody3->setContactTestBitmask(0x01);
    bullet3->setPhysicsBody(physicbody3);
    
    //定义运动方向
    auto moveBy1 = cocos2d::MoveBy::create(10.0f, direction1 * 1000);
    auto moveBy2 = cocos2d::MoveBy::create(10.0f, direction2 * 1000);
    auto moveBy3 = cocos2d::MoveBy::create(10.0f, direction3 * 1000);
    auto remove = cocos2d::RemoveSelf::create();
    //运动
    bullet1->runAction(cocos2d::Sequence::create(moveBy1, remove, nullptr));
    bullet2->runAction(cocos2d::Sequence::create(moveBy2, remove, nullptr));
    bullet3->runAction(cocos2d::Sequence::create(moveBy3, remove, nullptr));
    
}
