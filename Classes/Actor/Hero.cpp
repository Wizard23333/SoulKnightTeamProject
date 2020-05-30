
#include "Hero.h"
#include <iostream>
Hero::Hero(const std::string pngName, int blood, int energy, int sheild)
:_heroValue(blood, energy, sheild), Actor(pngName), _weapon(std::string("projectile.png"))
{
    changeWeapon = false;
    _sprite->setTag(999);
}

Hero * Hero::HeroCreate(const std::string pngName, int blood, int energy, int sheild)
{
    _heroValue.setBlood(blood);
    _heroValue.setEnergy(energy);
    _heroValue.setShield(sheild);
    _sprite->setTag(999);
    changeWeapon = false;
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
        this->moveAll(repeatRight);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        auto moveDown = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, -15));
        auto repeatDown = cocos2d::RepeatForever::create(moveDown);
        repeatDown->setTag(102);
        this->moveAll(repeatDown);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        auto moveUp = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, 15));
        auto repeatUp = cocos2d::RepeatForever::create(moveUp);
        repeatUp->setTag(103);
        this->moveAll(repeatUp);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
    {
        auto moveLeft = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(-15, 0));
        auto repeatLeft = cocos2d::RepeatForever::create(moveLeft);
        repeatLeft->setTag(104);
        this->moveAll(repeatLeft);
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
        this->stopMoveByTag(101);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        this->stopMoveByTag(102);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        this->stopMoveByTag(103);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
    {
        this->stopMoveByTag(104);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_G)
    {
        changeWeapon = false;
    }
    return true;
}

bool Hero::onTouchBegin(cocos2d::Touch* touch)
{
    
    if(_heroValue.energy >= _weapon.getCost())
    {
        this->attack(touch);
        
    
    }
    
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
     if(如果是子弹和人)
     {
     
     }
    */
    cocos2d::log("%d", nodeA->getTag());
    cocos2d::log("%d", nodeB->getTag());
    if(nodeA->getTag() == 999 && nodeB ->getTag() == 333)
    {
        cocos2d::log("afdd");
        nodeB->removeFromParentAndCleanup(true);
    }
    if(nodeB->getTag() == 999 && nodeA ->getTag() == 333)
    {
        cocos2d::log("abdsdf");
        nodeA->removeFromParentAndCleanup(true);
    }
    return true;
}

bool Hero::onContactSeparate(cocos2d::PhysicsContact & contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    return true;
}

void Hero::attack(cocos2d::Touch * touch)
{
    this->_weapon.shoot(touch);//传入点击位置射击//子弹射出点出点在武器自己的位置上
    this->_heroValue.setEnergy(_heroValue.energy - _weapon.getCost());//消耗能量
    //....
}

void Hero::colletWeapon(cocos2d::Node * weaponNode)
{
    /*
    _weapon.reset(weaponNode->getTag());//用节点的Tag来重新设置武器//
    weaponNode->removeFromParentAndCleanup(true)//清除放在地上的武器
    */
}




void Hero::moveAll(cocos2d::Action * move)
{
    auto move1 = move->clone();
    move1->setTag(move->getTag());
    this->_sprite->runAction(move1);
    //this->_weapon._sprite->runAction(move);
    
}

void Hero::stopMoveByTag(int tag)
{
    this->_sprite->stopActionByTag(tag);
    //this->_weapon._sprite->stopActionByTag(tag);
}
