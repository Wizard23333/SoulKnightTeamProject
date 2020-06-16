/*
  战斗场景基本组件
 */
#include "FightGroundScene.h"
#include "SimpleAudioEngine.h"
//#include "../cocos/audio/mac/CocosDenshion.h"

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
    
    visibleSize = Director::getInstance()->getVisibleSize();//可见范围大小
    originPoint = Director::getInstance()->getVisibleOrigin();//原点
    
    auto background = DrawNode::create();//背景
    background->drawSolidRect(originPoint, visibleSize, cocos2d::Color4F::GRAY);
    this->addChild(background, 0);
    
    auto audioBgm = CocosDenshion::SimpleAudioEngine::getInstance();
    isMusicPlaying = audioBgm->isBackgroundMusicPlaying() ? true : false;
    
    auto offMusic = MenuItemImage::create("MusicSelected.png", "MusicSelected.png");
    auto onMusic = MenuItemImage::create("MusicNormal.png", "MusicNormal.png");
    //add
    offMusic->setScale(0.15);
    onMusic->setScale(0.15);
    
    MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(FightGround::menucloseMusic, this),
        onMusic, offMusic, NULL
    );
    //musicItem->setPosition(Vec2(visibleSize.width - musicItem->getContentSize().width / 2, visibleSize.height - musicItem->getContentSize().height / 2));
    
    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(FightGround::menucloseCallBack, this));//退出按钮
    float x = originPoint.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = originPoint.y + visibleSize.height - closeItem->getContentSize().height/2 ;
    closeItem->setPosition(Vec2(x,y));
    musicItem->setPosition(Vec2(x, y - closeItem->getContentSize().height));
    auto menu = Menu::create(closeItem, musicItem, nullptr);//主菜单
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    //血条
    Monster::mstrNum = 4;
    char temp1[20];
    sprintf(temp1, "Blood:%d/%d", myHero._heroValue.blood, myHero._heroValue.fullBlood);
    blood = cocos2d::Label::createWithTTF(temp1, "fonts/Marker Felt.ttf", 30);
    blood->setColor(Color3B::RED);
    blood->setPosition(Vec2(blood->getContentSize().width / 2, visibleSize.height - blood->getContentSize().height));
    this->addChild(blood, 1);
    
    char temp2[20];
    sprintf(temp2, "Energy:%d/%d", myHero._heroValue.energy, myHero._heroValue.fullEnergy);
    energy = cocos2d::Label::createWithTTF(temp2, "fonts/Marker Felt.ttf", 30);
    energy->setColor(Color3B::BLUE);
    energy->setPosition(Vec2(energy->getContentSize().width / 2, visibleSize.height - blood->getContentSize().height - energy->getContentSize().height));
    this->addChild(energy, 1);
    
    char temp3[20];
    sprintf(temp3, "Sheild:%d/%d", myHero._heroValue.shield, myHero._heroValue.fullShield);
    sheild = cocos2d::Label::createWithTTF(temp3, "fonts/Marker Felt.ttf", 30);
    sheild->setColor(Color3B::BLACK);
    sheild->setPosition(Vec2(sheild->getContentSize().width / 2, visibleSize.height - sheild->getContentSize().height - blood->getContentSize().height - energy->getContentSize().height));
    this->addChild(sheild, 1);
    
    this->schedule(schedule_selector(FightGround::updateBlood), 0.1f);//血量更新
    
                   
    /*
    auto wall = Node::create();
    wall->addComponent(PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1, 0.0f)));
    wall->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
    this->addChild(wall);
    */
   // myHero.HeroCreate("Ninja.png");//创建英雄
    myHero = Hero("Knight.png");
    myHero._sprite->setPosition(Vec2(originPoint.x + 0.5 * visibleSize.width, originPoint.y + 0.5 * visibleSize.height));//设置位置
    myHero._sprite->setScale(0.08);
    
    myHero.setWeapon(6);//武器类型
    myHero._weapon._sprite->setPosition(myHero._sprite->getPosition());
    myHero._weapon._sprite->setScale(0.10);
    this->addChild(myHero._sprite, 1);
    this->addChild(myHero._weapon._sprite, 1);
    //myHero._sprite->setTag(999);//添加Tag值
    
    //myHero._heroValue.setBlood(5);//加血演示
    //myHero._heroValue.setEnergy(10);
    //添加药水
    potion1 = Potion("Blood.png");
    potion1._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 200));
    potion1._sprite->setScale(0.10);
    potion1._sprite->setTag(1);//药水的属性值
    potion1.hideSelf();
    this->addChild(potion1._sprite, 1);

    potion2 = Potion("Energy.png");
    potion2._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 200));
    potion2._sprite->setScale(0.10);
    potion2._sprite->setTag(2);
    potion2.hideSelf();
    this->addChild(potion2._sprite, 1);
    
    box1 = Box(1, 1);//加入宝箱
    box1._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 100));
    box1._sprite->setScale(0.5);
    box1.hideSelf();
    this->addChild(box1._sprite, 1);
    
    this->monsterinit();//初始化怪物设置
    
    this->schedule(schedule_selector(FightGround::controlMoveArea), 0.1f);//控制外围边界
    
    
    auto eventListener = EventListenerTouchOneByOne::create();//触摸事件监听
    eventListener->onTouchBegan = CC_CALLBACK_2(FightGround::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(FightGround::onTouchEnded, this);
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
    Director::getInstance()->pushScene(PauseScene::createScene());
}

void FightGround::menucloseMusic(cocos2d::Ref *pSender)
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
bool FightGround::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)//触摸的回调
{
    
    if(myHero.onTouchBegin(touch)== true)
        myHero._weapon.onTouchBegan(touch, unused_event);
    return true;
}
bool FightGround::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    
    myHero._weapon.onTouchEnded(touch, unused_event);
    return true;
}
bool FightGround::onContactBegan(cocos2d::PhysicsContact & contact)//碰撞的回调
{
    
    myHero.onContactBegin(contact);//成员函数处理碰撞信息//==false意味着没有节点被清除
    potion1.onContactpresolve(contact);
    potion2.onContactpresolve(contact);
    box1.onContactBegin(contact);
    if(box1.isOpen == true)
        box1._potion.onContactpresolve(contact);
    monster1.oncontactBegin(contact);
    monster2.oncontactBegin(contact);
    monster3.oncontactBegin(contact);
    monster4.oncontactBegin(contact);
    return true;
}

bool  FightGround::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)//按键按下的回调
{
    myHero.onKeyPressed(keycode);//成员函数处理键盘信息//下同
    potion1.onKeyPressed(keycode);
    potion2.onKeyPressed(keycode);
    if(box1.isOpen == true)
        box1._potion.onKeyPressed(keycode);
        
    return true;
}

bool FightGround::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    myHero.onKeyRelesed(keycode);
    potion1.onKeyReleased(keycode);
    potion2.onKeyReleased(keycode);
    if(box1.isOpen == true)
        box1._potion.onKeyReleased(keycode);

    return true;
}

void FightGround::monsterinit()//怪物初始化
{
    
    this->scheduleOnce(schedule_selector(FightGround::addmonster), 0.1f);//在0.1s后添加怪物
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(FightGround::automoveM), 1.0f);//每隔一秒怪物运动
    this->schedule(schedule_selector(FightGround::autoshootM), 3.0f);//每隔一秒怪物射击
    
}

void FightGround::addmonster(float dt)//创建并添加怪物
{
    
    monster1.monsterCreate(std::string("monster copy.png"), 20, 1);
    monster2.monsterCreate(std::string("monster copy.png"), 20, 2);
    monster3.monsterCreate(std::string("monster copy.png"), 20, 3);
    monster4.monsterCreate(std::string("monster copy.png"), 20, 4);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    monster1._sprite->setPosition(visibleSize.width * 0.33, visibleSize.height / 2);
    monster2._sprite->setPosition(visibleSize.width * 0.66, visibleSize.height / 2);
    monster3._sprite->setPosition(visibleSize.width * 0.77, visibleSize.height / 2);
    monster4._sprite->setPosition(visibleSize.width * 0.88, visibleSize.height / 2);
    monster1.setRemoteMstr();
    monster2.setRemoteMstr();
    monster3.setRemoteMstr();
    monster4.setCloseMstr();//设置近程怪物
    this->addChild(monster1._sprite, 1);
    this->addChild(monster2._sprite, 1);
    this->addChild(monster3._sprite, 1);
    this->addChild(monster4._sprite, 1);
    //monster1.setMonsterNum(4);
}

void FightGround::automoveM(float dt)
{
    monster1.autoMove();//用类的成员函数控制怪物的运动
    monster2.autoMove();
    monster3.autoMove();
    monster4.autoMove(myHero._sprite->getPosition());
    
}

void FightGround::autoshootM(float dt)//自动攻击
{
    auto destination = myHero._sprite->getPosition();//获取需要的坐标
    monster1.autoShoot(destination);
    monster2.autoShoot(destination);
    monster3.autoShoot(destination);
    
}

void FightGround::updateBlood(float dt)
{
    char temp1[20];
    sprintf(temp1, "Blood:%d/%d", myHero._heroValue.blood, myHero._heroValue.fullBlood);
    blood->setString(temp1);
    blood->setVisible(true);
    
    char temp2[20];
    sprintf(temp2, "Energy:%d/%d", myHero._heroValue.energy, myHero._heroValue.fullEnergy);
    energy->setString(temp2);
    energy->setVisible(true);
    
    char temp3[20];
    sprintf(temp3, "Sheild:%d/%d", myHero._heroValue.shield, myHero._heroValue.fullShield);
    sheild->setString(temp3);
    sheild->setVisible(true);
    
    if(myHero._heroValue.blood == 0)
    {
        //Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));

        Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Welcome::createScene()));
    }
    if(Monster::mstrNum == 0)
    {
        //Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Welcome::createScene()));
        //Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
        this->appearSprite();
    }
}

void FightGround::controlMoveArea(float dt)
{
    controlSprite(monster1._sprite);
    controlSprite(monster2._sprite);
    controlSprite(monster3._sprite);
    controlSprite(monster4._sprite);
    controlSprite(myHero._sprite);
    controlSprite(myHero._weapon._sprite);
}

void FightGround::controlSprite(Sprite *sprite)
{
    auto position = sprite->getPosition();
    if(position.x < originPoint.x || position.x > originPoint.x + visibleSize.width
       || position.y < originPoint.y || position.y > originPoint.y + visibleSize.height)
    {
        sprite->setOpacity(255);
        sprite->stopAllActions();
        auto moveDirect = Vec2(originPoint.x + visibleSize.width / 2 - position.x, originPoint.y + visibleSize.height / 2 - position.y);
        moveDirect.normalize();
        auto moveBack = cocos2d::MoveBy::create(0.1f, moveDirect * 20);
        sprite->runAction(moveBack);
    }
}

void FightGround::appearSprite()
{
    static int appeartimes = 0;
    if(appeartimes == 0)
    {
        potion1.appearSelf();
        potion2.appearSelf();
        box1.appearSelf();
        appeartimes++;
    }
    else
        return;
    
    
}
