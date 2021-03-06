
#include "Hero.h"
#include <iostream>
int Hero::weaponTag = 5;
Hero::Hero(const std::string pngName, int blood, int energy, int sheild)
:_heroValue(blood, energy, sheild), Actor(pngName), _weapon(std::string("Darts.png"))
{
    //changeWeapon = false;
    _sprite->setTag(999);
}

Hero * Hero::HeroCreate(const std::string pngName, int blood, int energy, int sheild)
{
    _heroValue.setBlood(blood);
    _heroValue.setEnergy(energy);
    _heroValue.setShield(sheild);
    _sprite->setTag(999);
    //changeWeapon = false;
    actorCreate(pngName);
    return this;
}

void Hero::setWeapon(int tag)
{
    _weapon = Weapon(parameter[tag].getpngname(), tag);
    weaponTag = tag;
}
bool Hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_D)
    {
        this->_sprite->setFlippedX(false);
        //this->_weapon._sprite->setFlippedY(false);
        this->_weapon._sprite->setRotation(0);
        auto moveRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(40, 0));
        auto repeatRight = cocos2d::RepeatForever::create(moveRight);
        repeatRight->setTag(101);
        this->moveAll(repeatRight);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        auto moveDown = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, -40));
        auto repeatDown = cocos2d::RepeatForever::create(moveDown);
        repeatDown->setTag(102);
        this->moveAll(repeatDown);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        auto moveUp = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, 40));
        auto repeatUp = cocos2d::RepeatForever::create(moveUp);
        repeatUp->setTag(103);
        this->moveAll(repeatUp);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
    {
        this->_sprite->setFlippedX(true);
        
        //this->_weapon._sprite->setFlippedY(true);
        this->_weapon._sprite->setRotation(180);
        auto moveLeft = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(-40, 0));
        auto repeatLeft = cocos2d::RepeatForever::create(moveLeft);
        repeatLeft->setTag(104);
        this->moveAll(repeatLeft);
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_G)
    {
        changeWeapon();
    }
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_R)
    {
        this->_heroValue.setShield(this->_heroValue.fullShield);
        this->_heroValue.setBlood(this->_heroValue.fullBlood);
        this->_heroValue.setEnergy(this->_heroValue.fullEnergy);
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
        //changeWeapon();
    }
    return true;
}

bool Hero::onTouchBegin(cocos2d::Touch* touch)
{
    
    if(_heroValue.energy >= _weapon.GetBulletenergycost())
    {
        this->attack(touch);
        auto dest = touch->getLocation();
        
        auto direction = Vec2(dest.x - _sprite->getPosition().x, dest.y - _sprite->getPosition().y);
        direction.normalize();
        auto rotateAngle = atan(direction.y / direction.x) / 3.14 * 180;
        rotateAngle = direction.x > 0 ? rotateAngle : rotateAngle + 180;
        _weapon._sprite->setRotation(-rotateAngle);
        return true;
    
    }
    else
    {
        return false;
    }
    
    
}
/*
武器拾起:
 
 
*/
bool Hero::onContactBegin(cocos2d::PhysicsContact & contact)
{
   
    /*
    if(如果是放在地上的武器和人的接触,并且changeWeapon == true (即按下了G键))//假设A是放在地上的武器的node
    {
     this->colletWeapon(nodeA)
    }
     if(如果是子弹和人)
     {
     
     }
    */
    //cocos2d::log("%d", nodeA->getTag());
    //cocos2d::log("%d", nodeB->getTag());
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA && nodeB)
    {
        auto posA = nodeA->getPosition();
        auto posB = nodeB->getPosition();
        log("%d",nodeA->getTag());
        log("%d",nodeB->getTag());
		int tagA = nodeA->getTag(), tagB = nodeB->getTag();
        if(posA == this->_sprite->getPosition() || posB == this->_sprite->getPosition())
        {
            if(tagA == 999 && tagB > 700 && tagB < 800)//子弹和英雄
            {
                this->getShot(nodeB->getTag() - 700);
                nodeB->removeFromParentAndCleanup(true);
            }
            if(tagB == 999 && tagA > 700 && tagA < 800)
            {
                this->getShot(nodeA->getTag() - 700);
                nodeA->removeFromParentAndCleanup(true);
            }
            if(tagA == 999 && tagB > 800 && tagB < 900)//近战怪物
            {
                this->getShot(nodeB->getTag() - 800);
                nodeB->setOpacity(255);
                nodeB->stopAllActions();
				auto pause = DelayTime::create(1.0f);
                nodeB->runAction(pause);
            }
            if(tagB == 999 && tagA > 800 && tagA < 900)
            {
                this->getShot(nodeA->getTag() - 800);
                nodeA->setOpacity(255);
                nodeA->stopAllActions();
                auto pause = DelayTime::create(1.0f);
                nodeA->runAction(pause);
            }
            if(tagA == 999 && (tagB >= 100 && tagB <= 150))//药水
            {
                getCue(nodeB->getTag() - 101);
            }
            if(tagB == 999 && (tagA >= 100 && tagA <= 150))
            {
                getCue(nodeA->getTag() - 101);
                
            }
        }
    }
    return true;
    //return false;
}

bool Hero::onContactSeparate(cocos2d::PhysicsContact & contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    return true;
}

void Hero::changeWeapon()
{
    auto weaponTag = _weapon._sprite->getTag();
    if(weaponTag <= 7)
        weaponTag++;
    else if(weaponTag == 8)
        weaponTag = 5;
    else
        log("error   !!!!");
    this->weaponTag = weaponTag;
    this->_weapon._sprite->setTag(weaponTag);
    this->_weapon.tagofbullet = _weapon._sprite->getTag() + 5;
    auto temp = Sprite::create(parameter[weaponTag].getpngname());
    auto temp_texture = temp->getTexture();
    auto scaleX = 0.1 * temp_texture->getContentSize().width / _weapon._sprite->getContentSize().width;
    auto scaleY = 0.1 * temp_texture->getContentSize().height / _weapon._sprite->getContentSize().height;
    _weapon._sprite->setTexture(temp_texture);
    _weapon._sprite->setScale(scaleX, scaleY);
    
   //if(this->_weapon._sprite->getRotation() == 180)
    {
        
      //  this->_weapon._sprite->setRotation(0);
        //this->_weapon._sprite->setFlippedY(true);
    }
    
}
void Hero::attack(cocos2d::Touch * touch)
{
    //this->_weapon.shoot(touch);//传入点击位置射击//子弹射出点出点在武器自己的位置上
    //log("$$$$$");
    this->_heroValue.setEnergy(_heroValue.energy - _weapon.GetBulletenergycost());//消耗能量
   
    //....
}

void Hero::getShot(int value)
{
    
    if(this->_heroValue.shield > 0)
    {
        this->_heroValue.setShield(this->_heroValue.shield - value);
    }
    else if(this->_heroValue.blood > 0)
    {
        this->_heroValue.setBlood(this->_heroValue.blood - value);
    }
    auto  fadeIn = FadeIn::create(0.2f);
    auto fadeOut = FadeOut::create(0.2f);
    this->_sprite->runAction(Sequence::create(fadeOut, fadeIn, nullptr));
    this->_weapon._sprite->runAction(Sequence::create(fadeOut->clone(), fadeIn->clone(), nullptr));
    char temp[5];
    sprintf(temp, "%d", value);
    auto label = Label::createWithTTF(temp, "fonts/Marker Felt.ttf", 20);
    label->setColor(Color3B::RED);
    label->setPosition(this->_sprite->getPosition());
    this->_sprite->getParent()->addChild(label, 1);
    auto moveDown = MoveBy::create(0.2f, Vec2(0, -20));
    auto removeSelf = RemoveSelf::create();
    label->runAction(Sequence::create(moveDown, fadeOut->clone(), removeSelf, nullptr));
}

void Hero::getCue(int value)
{
    auto bloodAdd = parameter[value].getparameter1();
    auto energyAdd = parameter[value].getparameter2();
    this->_heroValue.setBlood(_heroValue.blood + bloodAdd);
    this->_heroValue.setEnergy(_heroValue.energy + energyAdd);
    char temp1[5];
    char temp2[5];
    auto position = this->_sprite->getPosition();
    sprintf(temp1, "%d", bloodAdd);
    sprintf(temp2, "%d", energyAdd);
    auto bloodLabel = Label::createWithTTF(temp1, "fonts/Marker Felt.ttf", 20);
    auto energyLabel = Label::createWithTTF(temp2, "fonts/Marker Felt.ttf", 20);
    bloodLabel->setColor(Color3B::GREEN);
    energyLabel->setColor(Color3B::BLUE);
    bloodLabel->setPosition(Vec2(position.x - 10, position.y + 10));
    energyLabel->setPosition(Vec2(position.x + 10, position.y + 10));
    this->_sprite->getParent()->addChild(bloodLabel, 1);
    this->_sprite->getParent()->addChild(energyLabel, 1);
    auto moveUp = MoveBy::create(0.2, Vec2(0, 20));
    auto fadeOut = FadeOut::create(0.2f);
    auto removeSelf = RemoveSelf::create();
    bloodLabel->runAction(Sequence::create(moveUp, fadeOut, removeSelf, nullptr));
    energyLabel->runAction(Sequence::create(moveUp->clone(), fadeOut->clone(), removeSelf->clone(), nullptr));
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
    this->_weapon._sprite->runAction(move);
    this->_weapon._sprite->setPosition(this->_sprite->getPosition());
    
}

void Hero::stopMoveByTag(int tag)
{
    this->_sprite->stopActionByTag(tag);
    this->_weapon._sprite->stopActionByTag(tag);
    this->_weapon._sprite->setPosition(this->_sprite->getPosition());
}
