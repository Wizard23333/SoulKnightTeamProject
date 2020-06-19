#ifndef Hero_h
#define Hero_h
#include "cocos2d.h"
#include "Actor.h"
#include "Weapon.h"
#include "Props.h"

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
    void setBlood(int blood)
    {
        if(blood <= fullBlood && blood >= 0)
            this->blood = blood;
        else if(blood < 0)
            this->blood = 0;
        else if(blood >= fullBlood)
            this->blood = fullBlood;
    }
    void setEnergy(int energy)
    {
        if(energy <= fullEnergy && energy >= 0)
            this->energy = energy;
        else if(energy < 0)
            this->energy = 0;
        else if(energy >= fullEnergy)
            this->energy = fullEnergy;
        
    }
    void setShield(int shield)
    {
        if(shield <= fullShield && shield >= 0)
            this->shield = shield;
        else if(shield < 0)
            this->shield = 0;
        else if(shield >= fullShield)
            this->shield = fullShield;
        
    }
};

class Hero : public Actor
{
public:
    Weapon _weapon;//武器
    Hero(const std::string pngName = "HelloWorld.png", int blood = 100, int energy = 50, int sheild = 30);
    Hero * HeroCreate(const std::string pngName = "HelloWorld.png", int blood = 100, int energy = 50, int sheild = 30);
    void setWeapon(int tag = 5);
    static int weaponTag;
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onKeyRelesed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onTouchBegin(cocos2d::Touch * touch);
    bool onContactBegin(cocos2d::PhysicsContact & contact);
    bool onContactSeparate(cocos2d::PhysicsContact & contact);
    class  heroValue _heroValue;
private:
    void changeWeapon();
    void attack(cocos2d::Touch * touch);
    void getShot(int value = 1);
    void getCue(int value = 1);
    void colletWeapon(cocos2d::Node * weaponNode);
    void moveAll(cocos2d::Action * move);
    void stopMoveByTag(int tag);
    void usePotion();
};



#endif /* Hero_h */
