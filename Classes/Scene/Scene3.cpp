#include "FightGroundScene.h"
#include "SimpleAudioEngine.h"
//#include  "C:\Users\Dell\Desktop\cocos2d-x-3.17.2\cocos2d-x-3.17.2\cocos\audio\include\SimpleAudioEngine.h"
#include "Scene3.h"
//#include "../cocos/audio/mac/CocosDenshion.h"

USING_NS_CC;
int Scene3::s3_blood = 0;
int Scene3::s3_energy = 0;
int Scene3::s3_shield = 0;
int Scene3::s3_money = 0;
Scene * Scene3::createScene(int blood, int energy, int shield, int money)
{
    s3_blood = blood;
    s3_energy = energy;
    s3_shield = shield;
	s3_money = money;
    return Scene3::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Scene3::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    if(!Scene::initWithPhysics())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    originPoint = Director::getInstance()->getVisibleOrigin();
    
    auto audioBgm = CocosDenshion::SimpleAudioEngine::getInstance();
    isMusicPlaying = audioBgm->isBackgroundMusicPlaying() ? true : false;
    
    auto offMusic = MenuItemImage::create("MusicSelected.png", "MusicSelected.png");
    auto onMusic = MenuItemImage::create("MusicNormal.png", "MusicNormal.png");
    
    
    MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(Scene3::menucloseMusic, this),
        onMusic, offMusic, NULL
    );
    
    auto closeItem = MenuItemImage::create("pauce.png","pauce.png",CC_CALLBACK_1(Scene3::menucloseCallBack, this));
    
    float x = originPoint.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = originPoint.y + visibleSize.height - closeItem->getContentSize().height/2 ;
    closeItem->setPosition(Vec2(x,y));
    musicItem->setPosition(Vec2(x, y - closeItem->getContentSize().height));
    auto menu = Menu::create(closeItem, musicItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

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
	money->setPosition(Vec2(money->getContentSize().width / 2, visibleSize.height - sheild->getContentSize().height - blood->getContentSize().height - energy->getContentSize().height - money->getContentSize().height));
	this->addChild(money, 1);
    
    this->schedule(schedule_selector(Scene3::updateBlood), 0.1f);
        
    for (double i = 1; i <= 9;i=i+0.5)
    {
        for (double j = 1; j <= 9;j=j+0.5 )
        {
            if (i > 1 && i < 9 && j>1 && j < 9)
            {
                continue;
            }
            double k1 = 0.1 * i, k2 = 0.1 * j;
            Wall wall = Wall("wall2.png");
            wall._sprite->setPosition(Vec2(visibleSize.width * k1, visibleSize.height * k2));
            wall._sprite->setScale(0.10);
            this->addChild(wall._sprite);
        }
    }
    
    for(double i = 1; i <= 4;i=i+0.5)
    {
        double k1 = 0.1 * i;
        Wall wall = Wall("wall2.png");
        wall._sprite->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height * k1));
        wall._sprite->setScale(0.10);
        this->addChild(wall._sprite);
    }
    for(double i = 5; i <= 9;i=i+0.5)
    {
        double k1 = 0.1 * i;
        Wall wall = Wall("wall2.png");
        wall._sprite->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height * k1));
        wall._sprite->setScale(0.10);
        this->addChild(wall._sprite);
    }
    
    
    auto background = Sprite::create("backGround2.png");
    auto scaleX = visibleSize.width / background->getContentSize().width;
    auto scaleY = visibleSize.height / background->getContentSize().height;
    auto realScale = scaleX > scaleY ? scaleX : scaleY;
    background->setScale(realScale);
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, -1);
    
    myHero = Hero("Knight.png");
    myHero._heroValue.setBlood(s3_blood);
    myHero._heroValue.setEnergy(s3_energy);
    myHero._heroValue.setShield(s3_shield);
	myHero._heroValue.setMoney(s3_money);
    
    myHero._sprite->setPosition(Vec2(originPoint.x + 0.5 * visibleSize.width, originPoint.y + 0.5 * visibleSize.height));
    myHero._sprite->setScale(0.08);
    
    myHero.setWeapon(Hero::weaponTag);
    myHero._weapon._sprite->setPosition(myHero._sprite->getPosition());
    myHero._weapon._sprite->setScale(0.10);
    this->addChild(myHero._sprite, 1);
    this->addChild(myHero._weapon._sprite, 1);
    this->schedule(schedule_selector(Scene3::valueAdd), 1.0f);
    
    //添加药水
    potion1 = Potion("Blood.png");
    potion1._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 200));
    potion1._sprite->setScale(0.10);
    potion1._sprite->setTag(1);
    potion1.hideSelf();
    this->addChild(potion1._sprite, 1);

    potion2 = Potion("Energy.png");
    potion2._sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 200));
    potion2._sprite->setScale(0.10);
    potion2._sprite->setTag(2);
    potion2.hideSelf();
    this->addChild(potion2._sprite, 1);
    
    box1 = Box(1, 1);
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
    appearTime = 0;
    
    //初始化怪物设置
    this->monsterinit();
    
    this->schedule(schedule_selector(Scene3::controlMoveArea), 0.1f);
    
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(Scene3::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(Scene3::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Scene3::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(Scene3::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(Scene3::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    return true;
}

void Scene3::menucloseCallBack(Ref* pSender)
{
    Director::getInstance()->pushScene(PauseScene::createScene());
}

void Scene3::menucloseMusic(cocos2d::Ref *pSender)
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (isMusicPlaying == true)
    {
        audio->pauseBackgroundMusic();
        isMusicPlaying = false;
    }
    else
    {
        audio->resumeBackgroundMusic();
        isMusicPlaying = true;
    }
}
void Scene3::nextScene()
{
	myHero._heroValue.setMoney(myHero._heroValue.money + 21);
    s3_blood = myHero._heroValue.blood;
    s3_energy = myHero._heroValue.energy;
    s3_shield = myHero._heroValue.shield;
	s3_money = myHero._heroValue.money;
    Director::getInstance()->replaceScene(bossScene::createScene(s3_blood, s3_energy, s3_shield, s3_money));
}

bool Scene3::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    
    if(myHero.onTouchBegin(touch)== true)
        myHero._weapon.onTouchBegan(touch, unused_event);
    return true;
}

bool Scene3::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    
    myHero._weapon.onTouchEnded(touch, unused_event);
    return true;
}

bool Scene3::onContactBegan(cocos2d::PhysicsContact & contact)
{
    myHero.onContactBegin(contact);
    potion1.onContactpresolve(contact);
    potion2.onContactpresolve(contact);
    box1.onContactBegin(contact);
    if(box1.isOpen == true)
        box1._potion.onContactpresolve(contact);
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

bool  Scene3::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    myHero.onKeyPressed(keycode);
    potion1.onKeyPressed(keycode);
    potion2.onKeyPressed(keycode);
    if(box1.isOpen == true)
        box1._potion.onKeyPressed(keycode);
    return true;
}

bool Scene3::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    myHero.onKeyRelesed(keycode);
    potion1.onKeyReleased(keycode);
    potion2.onKeyReleased(keycode);
    if(box1.isOpen == true)
        box1._potion.onKeyReleased(keycode);
    return true;
}

void Scene3::monsterinit()
{
    this->addmonster(1);
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(Scene3::automoveM), 1.0f);
    this->schedule(schedule_selector(Scene3::autoshootM), 1.5f);
}

void Scene3::addmonster(float dt)
{
    
    monster1 = Monster(std::string("monster4.png"), std::string("bullet4.png"), 20, 1);
    monster2 = Monster(std::string("monster4.png"), std::string("bullet4.png"), 30, 2);
    monster3 = Monster(std::string("monster4.png"), std::string("bullet4.png"), 30, 2);
    monster4 = Monster(std::string("monster4.png"), std::string("bullet4.png"), 30, 2);
    monster5.monsterCreate(std::string("monster5.png"), 30, 3);
    monster6.monsterCreate(std::string("monster5.png"), 50, 3);
    monster7.monsterCreate(std::string("monster2.png"), 50, 3);
    
    monster1._sprite->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2 - 130);
    monster2._sprite->setPosition(visibleSize.width / 2 - 130, visibleSize.height / 2 - 50);
    monster3._sprite->setPosition(visibleSize.width / 2 + 140, visibleSize.height / 2 + 40);
    monster4._sprite->setPosition(visibleSize.width / 2 + 170, visibleSize.height / 2 - 180);
    monster5._sprite->setPosition(visibleSize.width / 2 - 45, visibleSize.height / 2 + 160);
    monster6._sprite->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2 - 200);
    monster7._sprite->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2 + 100);
    
    monster1.setRemoteMstr();
    monster2.setRemoteMstr();
    monster3.setRemoteMstr();
    monster4.setRemoteMstr();
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

    Monster::mstrNum = 7;

}

void Scene3::automoveM(float dt)
{
    monster1.autoMove();
    monster2.autoMove();
    monster3.autoMove();
    monster4.autoMove();
    monster5.autoMove(myHero._sprite->getPosition());
    monster6.autoMove(myHero._sprite->getPosition());
    monster7.autoMove(myHero._sprite->getPosition());
}

void Scene3::autoshootM(float dt)
{
    auto destination = myHero._sprite->getPosition();
    monster1.autoShoot(destination);
    monster2.autoShoot(destination);
    monster3.autoShoot(destination);
    monster4.autoShoot(destination);
}

void Scene3::updateBlood(float dt)
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
	sprintf(temp4, "Money:%d", myHero._heroValue.money + 3 * (7 - Monster::mstrNum));
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

void Scene3::valueAdd(float dt)
{
    myHero._heroValue.setShield(myHero._heroValue.shield + 1);
}
void Scene3::controlMoveArea(float dt)
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

void Scene3::controlSprite(Sprite *sprite)
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

void Scene3::controlMovingActor(PhysicsContact &contact)
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
}
void Scene3::appearSprite()
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
