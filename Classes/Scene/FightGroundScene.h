#ifndef FightGroundScene_h
#define FightGroundScene_h
#include "HelloWorldScene.h"
#include "PauseScene.h"
#include "WelcomeScene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
#include "Potion.h"
#include "Box.h"
#include "Wall.h"
USING_NS_CC;
class FightGround : public cocos2d::Scene
{
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    void menucloseCallBack(cocos2d::Ref * pSender);
    void menucloseMusic(cocos2d::Ref * pSender);
    void nextScene();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    bool onContactBegan(cocos2d::PhysicsContact &);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    CREATE_FUNC(FightGround);
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
    static int fgs_blood;
    static int fgs_energy;
    static int fgs_shield;
    int appearTime;
    Hero myHero;
    Potion potion1;
    Potion potion2;
    Props gate;
    Box box1;
    Monster monster1;
    Monster monster2;
    Monster monster3;
    Monster monster4;
    Monster monster5;
    Monster monster6;
    Monster monster7;
};


#endif /* FightGroundScene_h */
