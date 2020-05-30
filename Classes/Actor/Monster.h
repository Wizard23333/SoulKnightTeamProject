#ifndef Monster_h
#define Monster_h
#include "Actor.h"
class Monster : public Actor
{
public:
    Monster(const std::string pngName = "HelloWorld.png", int Blood = 20, int atk = 2);
    Monster * monsterCreate(const std::string pngName = "HelloWorld.png", int Blood = 20, int atk = 2);
    void autoMove();
    
private:
    int blood;
    int ATK;
    cocos2d::Sprite * _bulletSprite;
    void autoShoot();
    bool isDead();
    
};

#endif /* Monster_h */
