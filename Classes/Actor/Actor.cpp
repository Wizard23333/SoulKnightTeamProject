

#include "Actor.h"

Actor::Actor(const std::string name)
{
    _sprite = cocos2d::Sprite::create(name);
    auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody->setDynamic(false);
    physicbody->setContactTestBitmask(0x01);
    this->_sprite->setPhysicsBody(physicbody);
}

Actor * Actor::actorCreate(const std::string name)
{
    _sprite = cocos2d::Sprite::create(name);
    auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody->setDynamic(false);
    physicbody->setContactTestBitmask(0x01);
    this->_sprite->setPhysicsBody(physicbody);
    return this;
}
