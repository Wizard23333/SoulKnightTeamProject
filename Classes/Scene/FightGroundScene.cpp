/*
  战斗场景基本组件
 */
#include "FightGroundScene.h"
#include "SimpleAudioEngine.h"

//#include "C:\Users\Dell\Desktop\cocos2d-x-3.17.2\cocos2d-x-3.17.2\cocos\audio\include\SimpleAudioEngine.h"
//#include "../cocos/audio/mac/CocosDenshion.h"

USING_NS_CC;
Scene * FightGround::createScene()
{
    return FightGround::create();
}

int FightGround::fgs_shield = 0;
int FightGround::fgs_blood = 0;
int FightGround::fgs_energy = 0;
int FightGround::fgs_money = 0;
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
    /*
    auto background = DrawNode::create();//背景
    background->drawSolidRect(originPoint, visibleSize, cocos2d::Color4F::GRAY);
    this->addChild(background, 0);
    */
    auto audioBgm = CocosDenshion::SimpleAudioEngine::getInstance();
    isMusicPlaying = audioBgm->isBackgroundMusicPlaying() ? true : false;
    
    auto offMusic = MenuItemImage::create("MusicSelected.png", "MusicSelected.png");
    auto onMusic = MenuItemImage::create("MusicNormal.png", "MusicNormal.png");
    //add
   
    
    MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(FightGround::menucloseMusic, this),
        onMusic, offMusic, NULL
    );
    
    auto closeItem = MenuItemImage::create("pauce.png","pauce.png",CC_CALLBACK_1(FightGround::menucloseCallBack, this));//退出按钮
    float x = originPoint.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = originPoint.y + visibleSize.height - closeItem->getContentSize().height/2 ;
    closeItem->setPosition(Vec2(x,y));
    musicItem->setPosition(Vec2(x, y - closeItem->getContentSize().height));
    auto menu = Menu::create(closeItem, musicItem, nullptr);//主菜单
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    //血条
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

	char temp4[20];
	sprintf(temp4, "Money:%d", myHero._heroValue.money);
	money = cocos2d::Label::createWithTTF(temp4, "fonts/Marker Felt.ttf", 30);
	money->setColor(Color3B::YELLOW);
	money->setPosition(Vec2(money->getContentSize().width / 2, visibleSize.height - sheild->getContentSize().height - blood->getContentSize().height - energy->getContentSize().height-money->getContentSize().height));
	this->addChild(money, 1);
    
    this->schedule(schedule_selector(FightGround::updateBlood), 0.1f);//血量更新
    
                   
    /*
    auto wall = Node::create();
    wall->addComponent(PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1, 0.0f)));
    wall->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
    this->addChild(wall);
    */
    
    for (double i = 1; i <= 9;i=i+0.5)
    {
        for (double j = 1; j <= 9;j=j+0.5 )
        {
            if (i > 1 && i < 9 && j>1 && j < 9)
            {
                continue;
            }
            double k1 = 0.1 * i, k2 = 0.1 * j;
            Wall wall = Wall("wall1.png");
            wall._sprite->setPosition(Vec2(visibleSize.width * k1, visibleSize.height * k2));
            wall._sprite->setScale(0.10);
            this->addChild(wall._sprite);
        }
    }
    
    auto background = Sprite::create("backGround1.png");
    auto scaleX = visibleSize.width / background->getContentSize().width;
    auto scaleY = visibleSize.height / background->getContentSize().height;
    auto realScale = scaleX > scaleY ? scaleX : scaleY;
    background->setScale(realScale);
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, -1);
    
           // myHero.HeroCreate("Ninja.png");//创建英雄
    myHero = Hero("Knight.png");
    myHero._sprite->setPosition(Vec2(originPoint.x + 0.5 * visibleSize.width, originPoint.y + 0.5 * visibleSize.height));//设置位置
    myHero._sprite->setScale(0.08);
    
    myHero.setWeapon(5);//武器类型
    myHero._weapon._sprite->setPosition(myHero._sprite->getPosition());
    myHero._weapon._sprite->setScale(0.10);
    this->addChild(myHero._sprite, 1);
    this->addChild(myHero._weapon._sprite, 1);
    this->schedule(schedule_selector(FightGround::valueAdd), 1.0f);
    //myHero._sprite->setTag(999);//添加Tag值
    
    //myHero._heroValue.setBlood(5);//加血演示
    //myHero._heroValue.setEnergy(10);
    //添加药水
    potion2 = Potion("Energy.png");
    potion2._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 50));
    potion2._sprite->setScale(0.10);
    potion2._sprite->setTag(2);
    potion2.hideSelf();
    this->addChild(potion2._sprite, 1);
    
    potion1 = Potion("Blood.png");
    potion1._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 100));
    potion1._sprite->setScale(0.10);
    potion1._sprite->setTag(1);//药水的属性值
    potion1.hideSelf();
    this->addChild(potion1._sprite, 1);
    
    
    
    

    
    
    box1 = Box(1, 1);//加入宝箱
    box1._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 100));
    box1._sprite->setScale(0.5);
    box1.hideSelf();
    this->addChild(box1._sprite, 1);
    
    gate = Props("deliverGate.png");
    gate._sprite->setPosition(visibleSize.width - 100, visibleSize.height / 2);
    gate._sprite->setScale(0.8);
    gate._sprite->setTag(1001);
    gate.hideSelf();
    this->addChild(gate._sprite, 1);
    appearTime = 0;//使精灵只出现一次
    
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
void FightGround::nextScene()
{
	myHero._heroValue.setMoney(myHero._heroValue.money + 7);

    fgs_blood = myHero._heroValue.blood;
    fgs_energy = myHero._heroValue.energy;
    fgs_shield = myHero._heroValue.shield;
	fgs_money = myHero._heroValue.money;
    Director::getInstance()->replaceScene(Scene1::createScene(fgs_blood, fgs_energy, fgs_shield, fgs_money));
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
	{ 
		//log("hbiposition.x=%f bhauposition.y=%f", box1._potion._sprite->getPosition().x, box1._potion._sprite->getPosition().y);
		//box1._potion._sprite->setPosition(box1._potion._sprite->getPosition().x, box1._potion._sprite->getPosition().y);
        box1._potion.onContactpresolve(contact);
	}
    monster1.oncontactBegin(contact);
    monster2.oncontactBegin(contact);
    monster3.oncontactBegin(contact);
    monster4.oncontactBegin(contact);
    monster5.oncontactBegin(contact);
    monster6.oncontactBegin(contact);
    monster7.oncontactBegin(contact);
    controlMovingActor(contact);
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
    
    //this->scheduleOnce(schedule_selector(FightGround::addmonster), 0.1f);//在0.1s后添加怪物
    this->addmonster(1);
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(FightGround::automoveM), 1.0f);//每隔一秒怪物运动
    this->schedule(schedule_selector(FightGround::autoshootM), 3.0f);//每隔一秒怪物射击
    
}

void FightGround::addmonster(float dt)//创建并添加怪物
{
    
    monster1 = Monster(std::string("monster1.png"), std::string("bullet1.png"), 20, 5);
    monster2 = Monster(std::string("monster1.png"), std::string("bullet1.png"), 20, 4);
    monster3 = Monster(std::string("monster1.png"), std::string("bullet1.png"), 20, 5);
    monster4.monsterCreate(std::string("monster2.png"), 30, 8);
    monster5.monsterCreate(std::string("monster2.png"), 30, 8);
    monster6.monsterCreate(std::string("monster2.png"), 30, 9);
    monster7.monsterCreate(std::string("monster2.png"), 30, 9);
    monster1._sprite->setPosition(visibleSize.width * 0.33, visibleSize.height / 2);
    monster2._sprite->setPosition(visibleSize.width * 0.66, visibleSize.height / 2);
    monster3._sprite->setPosition(visibleSize.width * 0.77, visibleSize.height / 2);
    monster4._sprite->setPosition(visibleSize.width / 2 - 50, visibleSize.height / 2 -90);
    monster5._sprite->setPosition(visibleSize.width / 2 -200, visibleSize.height / 2 + 50);
    monster6._sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
    monster7._sprite->setPosition(visibleSize.width / 2+80 , visibleSize.height / 2 - 50);
    
    monster1.setRemoteMstr();
    monster2.setRemoteMstr();
    monster3.setRemoteMstr();
    monster4.setCloseMstr();//设置近程怪物
    monster5.setCloseMstr();
    monster6.setCloseMstr();
    monster7.setCloseMstr();
    this->addChild(monster1._sprite, 1);
    this->addChild(monster2._sprite, 1);
    this->addChild(monster3._sprite, 1);
    this->addChild(monster4._sprite, 1);
    this->addChild(monster5._sprite, 1);
    this->addChild(monster6._sprite, 1);
    this->addChild(monster7._sprite, 1);
    //monster1.setMonsterNum(4);
    Monster::mstrNum = 7;

}

void FightGround::automoveM(float dt)
{
    monster1.autoMove();//用类的成员函数控制怪物的运动
    monster2.autoMove();
    monster3.autoMove();
    monster4.autoMove(myHero._sprite->getPosition());
    monster5.autoMove(myHero._sprite->getPosition());
    monster6.autoMove(myHero._sprite->getPosition());
    monster7.autoMove(myHero._sprite->getPosition());
    
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

	char temp4[20];
	sprintf(temp4, "Money:%d", myHero._heroValue.money+(7-Monster::mstrNum));
	money->setString(temp4);
	money->setVisible(true);
    
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
void FightGround::valueAdd(float dt)
{
    myHero._heroValue.setShield(myHero._heroValue.shield + 1);
}

void FightGround::controlMoveArea(float dt)
{
    controlSprite(monster1._sprite);
    controlSprite(monster2._sprite);
    controlSprite(monster3._sprite);
    controlSprite(monster4._sprite);
    controlSprite(monster5._sprite);
    controlSprite(monster6._sprite);
    controlSprite(monster7._sprite);
    controlSprite(myHero._sprite);
    controlSprite(myHero._weapon._sprite);
}

void FightGround::controlSprite(Sprite *sprite)
{
    auto position = sprite->getPosition();
    if(position.x < originPoint.x + 130 || position.x > originPoint.x + visibleSize.width - 130
       || position.y < originPoint.y + 90 || position.y > originPoint.y + visibleSize.height - 90)
    {
        sprite->setOpacity(255);
        sprite->stopAllActions();
        auto moveDirect = Vec2(originPoint.x + visibleSize.width / 2 - position.x, originPoint.y + visibleSize.height / 2 - position.y);
        moveDirect.normalize();
        auto moveBack = cocos2d::MoveBy::create(0.1f, moveDirect * 20);
        sprite->runAction(moveBack);
    }
}

void FightGround::controlMovingActor(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA && nodeB)
    {
        auto posA = nodeA->getPosition();
        auto posB = nodeB->getPosition();
        auto tagA = nodeA->getTag();
        auto tagB = nodeB->getTag();
        if(tagA == 15 && tagB != 15)
        {
            if(tagB == 999 || (tagB > 800 && tagB < 900) || (tagB >= 5 && tagB <= 8))//英雄和怪物和武器a
            {
                nodeB->setOpacity(255);
                nodeB->stopAllActions();
                auto moveDirect = Vec2(posB.x - posA.x, posB.y - posA.y);
                moveDirect.normalize();
                auto moveBack = MoveBy::create(0.1f, moveDirect * 10);
                nodeB->runAction(moveBack);
            }
            if((tagB > 700 && tagB < 800) || (tagB >= 10 && tagB <= 13))
            {
                nodeB->removeFromParentAndCleanup(true);
            }
            
        }
        if(tagB == 15 && tagA != 15)
        {
            if(tagA == 999 || (tagA > 800 && tagA < 900) || (tagB >= 5 && tagB <= 8))//英雄和怪物武器
            {
                nodeA->setOpacity(255);
                nodeA->stopAllActions();
                auto moveDirect = Vec2(posA.x - posB.x, posA.y - posB.y);
                moveDirect.normalize();
                auto moveBack = MoveBy::create(0.1f, moveDirect * 10);
                nodeA->runAction(moveBack);
            }
            if((tagA > 700 && tagA < 800) || (tagA >= 10 && tagA <= 13))
            {
                nodeA->removeFromParentAndCleanup(true);
            }
        }
        if(tagB + tagA == 2000)
        {
            this->nextScene();
        }
    }
    myHero._weapon._sprite->setPosition(myHero._sprite->getPosition());
    log("###%d###", Monster::mstrNum);
    log("appeartimes: %d", appearTime);
}
void FightGround::appearSprite()
{
    if(appearTime == 0)
    {
        potion1._sprite->setPosition(Vec2(myHero._sprite->getPosition().x - 50, myHero._sprite->getPosition().y));
        potion2._sprite->setPosition(Vec2(myHero._sprite->getPosition().x, myHero._sprite->getPosition().y + 50));
        box1._sprite->setPosition(Vec2(myHero._sprite->getPosition().x + 50, myHero._sprite->getPosition().y));
        potion1.appearSelf();
        potion2.appearSelf();
        box1.appearSelf();
        gate.appearSelf();
        appearTime++;
    }
    else
        return;
}
