#ifndef Monster_h
#define Monster_h
#include "Actor.h"
#include "Props.h"
USING_NS_CC;
class Monster : public Actor
{
public:
    Monster(const std::string pngName = "HelloWorld.png", int Blood = 20, int atk = 2);
    Monster * monsterCreate(const std::string pngName = "HelloWorld.png", int Blood = 20, int atk = 2);
    void autoMove(Vec2 destination = Vec2(0, 0));
    void autoShoot(Vec2 destination = Vec2(0, 0));
    void setCloseMstr();
    int getATK() { return ATK; }
    void oncontactBegin(PhysicsContact & contact);
    void getShot(int value = 1);
    void setDead();
private:
    int blood;
    int ATK;
    cocos2d::Sprite * _bulletSprite;
    //void autoShoot();
    bool isDead();
    
};

#endif /* Monster_h */
