
#ifndef Actor_h
#define Actor_h

#include "cocos2d.h"
#include "constValues.h"
class Actor
{
public:
    cocos2d::Sprite *_sprite;
    Actor(const std::string name = "HelloWorld.png");
    Actor * actorCreate(const std::string name = "HelloWorld.png");
    cocos2d::Sprite * getSprite(void) { return _sprite; }
    //virtual bool onContactBegin(cocos2d::PhysicsContact & contact);
private:
    
};




#endif /* Actor_h */
