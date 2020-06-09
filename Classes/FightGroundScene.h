#ifndef FightGroundScene_h
#define FightGroundScene_h
#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
#include "Potion.hpp"
USING_NS_CC;
class FightGround : public cocos2d::Scene
{
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    void menucloseCallBack(cocos2d::Ref * pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
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
    Label * blood;
    Label * energy;
    Label * sheild;
    Hero myHero;
    Potion potion1;
    Potion potion2;
    Monster monster1;
    Monster monster2;
    Monster monster3;
};


#endif /* FightGroundScene_h */
