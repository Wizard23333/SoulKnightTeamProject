#ifndef Hero_h
#define Hero_h
#include "cocos2d.h"
#include "Actor.h"

class heroValue
{
public:
    int fullBlood;
    int blood;
    int fullEnergy;
    int energy;
    int fullShield;
    int shield;
    heroValue(int a = 10, int b = 20, int c = 2)
    {
        fullBlood = blood = a;
        fullEnergy = energy = b;
        fullShield = shield = c;
    }
};

class Hero : public Actor
{
public:
    Hero(const std::string pngName = "HelloWorld.png", int blood = 10, int energy = 20, int sheild = 2);
    Hero * HeroCreate(const std::string pngName);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onKeyRelesed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onTouchBegin(cocos2d::Touch * touch);
    bool onContactBegin(cocos2d::PhysicsContact & contact);
    bool onContactSeparate(cocos2d::PhysicsContact & contact);
private:
    class  heroValue _heroValue;
    //weapon _weapon;//武器
    bool changeWeapon;
    void attack(cocos2d::Touch * touch);
    void colletWeapon(cocos2d::Node * weaponNode);
    void usePotion();
    void setBlood();
    void setEnergy();
    void setSheild();
    
};

#endif /* Hero_h */
