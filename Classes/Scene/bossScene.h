
#ifndef bossScene_h
#define bossScene_h
#include "HelloWorldScene.h"
#include "PauseScene.h"
#include "WelcomeScene.h"
#include "FightGroundScene.h"
#include "Scene3.h"
#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
#include "Potion.h"
#include "Box.h"
#include "Wall.h"
USING_NS_CC;
class bossScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene * createScene(int blood = 100, int energy = 50, int shield = 30, int money=0);
    virtual bool init();
    void menucloseCallBack(cocos2d::Ref * pSender);
    void menucloseMusic(cocos2d::Ref * pSender);
    void nextScene();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    bool onContactBegan(cocos2d::PhysicsContact &);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    CREATE_FUNC(bossScene);
private:
    void monsterinit();//*****
    void addmonster(float dt);//*****
    void automoveM(float dt);//*****
    void autoshootM(float dt);//****
    void updateBlood(float dt);
    void valueAdd(float dt);
    void controlMoveArea(float dt);
    void controlSprite(Sprite * sprite);
    void controlMovingActor(PhysicsContact & contact);
    void appearSprite();
    bool isMusicPlaying;
    Size visibleSize;
    Vec2 originPoint;
    Label * blood;
    Label * energy;
    Label * sheild;
	Label * money;
    static int s3_blood;
    static int s3_energy;
    static int s3_shield;
	static int s3_money;
    int appearTime;
    Hero myHero;
    Potion potion1;
    Potion potion2;
    Props gate;
    Box box1;
    Monster boss;
    int shootAngle;
    
    
};

#endif /* bossScene_h */
