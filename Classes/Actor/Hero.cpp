#include<Hero.h>

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
    _weapon = Weapon(parameter[tag].getpngname());
	_weapon._sprite->setTag(tag);
}
bool Hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
    if(keycode == cocos2d::EventKeyboard::KeyCode::KEY_D)
    {
        this->_sprite->setFlippedX(false);
        this->_weapon._sprite->setFlippedY(true);
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
        this->_weapon._sprite->setFlippedY(true);
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
        if(posA == this->_sprite->getPosition() || posB == this->_sprite->getPosition())
        {
            if(nodeA->getTag() == 999 && nodeB ->getTag() > 700 && nodeB->getTag() < 800)//子弹和英雄
            {
                //cocos2d::log("afdd");
                this->getShot(nodeB->getTag() - 700);
                nodeB->removeFromParentAndCleanup(true);
                //return true;
            }
            if(nodeB->getTag() == 999 && nodeA ->getTag() > 700 && nodeA->getTag() < 800)
            {
                //cocos2d::log("abdsdf");
                this->getShot(nodeA->getTag() - 700);
                nodeA->removeFromParentAndCleanup(true);
                //return true;
            }
            if(nodeA->getTag() == 999 && nodeB->getTag() > 800 && nodeB->getTag() < 900)//近战怪物
            {
                
                this->getShot(nodeB->getTag() - 800);
            }
            if(nodeB->getTag() == 999 && nodeA->getTag() > 800 && nodeA->getTag() < 900)
            {
                this->getShot(nodeA->getTag() - 800);
            }
            if(nodeA->getTag() == 999 && (nodeB->getTag() >= 100 && nodeB->getTag() <= 150))//药水
            {
                getCue(nodeB->getTag() - 101);
            }
            if(nodeB->getTag() == 999 && (nodeA->getTag() >= 100 && nodeA->getTag() <= 150))
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
    this->_weapon._sprite->setTag(weaponTag);
    this->_weapon.tagofbullet = _weapon._sprite->getTag() + 5;
    auto temp = Sprite::create(parameter[weaponTag].getpngname());
    auto temp_texture = temp->getTexture();
    auto scaleX = 0.1 * temp->getContentSize().width / _weapon._sprite->getContentSize().width;
    auto scaleY = 0.1 * temp->getContentSize().height / _weapon._sprite->getContentSize().height;
    _weapon._sprite->setTexture(temp_texture);
    _weapon._sprite->setScale(scaleX, scaleY);
    
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
    
}

void Hero::stopMoveByTag(int tag)
{
    this->_sprite->stopActionByTag(tag);
   this->_weapon._sprite->stopActionByTag(tag);
}
