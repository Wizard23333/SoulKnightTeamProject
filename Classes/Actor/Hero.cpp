
#include "Hero.h"
#include <iostream>
Hero::Hero(const std::string pngName, int blood, int energy, int sheild)
:_heroValue(blood, energy, sheild), Actor(pngName)
{
    changeWeapon = false;
}

Hero * Hero::HeroCreate(const std::string pngName)
{
    actorCreate(pngName);
    return this;
}

bool Hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_D)
    {
        auto moveRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(15, 0));
        auto repeatRight = cocos2d::RepeatForever::create(moveRight);
        repeatRight->setTag(101);
        this->_sprite->runAction(repeatRight);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        auto moveDown = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, -15));
        auto repeatDown = cocos2d::RepeatForever::create(moveDown);
        repeatDown->setTag(102);
        this->_sprite->runAction(repeatDown);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        auto moveUp = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, 15));
        auto repeatUp = cocos2d::RepeatForever::create(moveUp);
        repeatUp->setTag(103);
        this->_sprite->runAction(repeatUp);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
    {
        auto moveLeft = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(-15, 0));
        auto repeatLeft = cocos2d::RepeatForever::create(moveLeft);
        repeatLeft->setTag(104);
        this->_sprite->runAction(repeatLeft);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_G)
    {
        changeWeapon = true;
    }
    return true;
}

bool Hero::onKeyRelesed(cocos2d::EventKeyboard::KeyCode keycode)
{
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_D)
    {
        this->_sprite->stopActionByTag(101);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        this->_sprite->stopActionByTag(102);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        this->_sprite->stopActionByTag(103);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
    {
        this->_sprite->stopActionByTag(104);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_G)
    {
        changeWeapon = false;
    }
    return true;
}

bool Hero::onTouchBegin(cocos2d::Touch* touch)
{
    /*
    if(_heroValue.energy >= _weapon.getCost())
     {
      this-> attack(touch);
     }
    ....
    */
    return true;
}
/*
武器拾起:
 
 
*/
bool Hero::onContactBegin(cocos2d::PhysicsContact & contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    /*
    if(如果是放在地上的武器和人的接触,并且changeWeapon == true (即按下了G键))//假设A是放在地上的武器的node
    {
     this->colletWeapon(nodeA)
    }
    */
    return true;
}

bool onContactSeparate(cocos2d::PhysicsContact & contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    
    
    return true;
}
void Hero::attack(cocos2d::Touch * touch)
{
    //this->_weapon.shoot(touch);//传入点击位置射击//子弹射出点出点在武器自己的位置上
    //_heroValue->setEnergy(_heroValue.energy - _weapon.getCost);//消耗能量
    //....
    
}

void Hero::colletWeapon(cocos2d::Node * weaponNode)
{
    /*
    _weapon.reset(weaponNode->getTag());//用节点Tag来重新设置武器
    weaponNode->removeFromParentAndCleanup(true)//清除放在地上的武器
    */
}


