#include "Monster.h"
int Monster::mstrNum = 0;
/*
Monster::Monster(const std::string pngName, int Blood, int atk)
:blood(Blood), Actor(pngName), ATK(atk)
{
    _sprite->setTag(800 + atk);
    _bulletName = "Bullet2.png";
    
}
*/
Monster::Monster(const std::string pngName, const std::string bulletName, int Blood, int atk)
:blood(Blood), Actor(pngName), ATK(atk)
{
    _sprite->setTag(800 + atk);
    _bulletName = bulletName;
}

Monster * Monster::monsterCreate(const std::string pngName, int Blood, int atk)
{
    actorCreate(pngName);
    blood = Blood;
    ATK = atk;
    _bulletName = "Bullet2.png";
    _sprite->setTag(800 + atk);
    
    return this;
}

bool Monster::isDead()
{
    if(blood <= 0)
    {
        return true;
    }
    else
        return false;
}

void Monster::autoMove(Vec2 destination)//怪物的随机运动
{
    if(this->isDead())
        return;
    if(destination != Vec2(0, 0))
    {
        auto monsterPos = this->_sprite->getPosition();
        auto direction = Vec2(destination.x - monsterPos.x, destination.y - monsterPos.y);
        direction.normalize();
        auto moveBy = MoveBy::create(1.0f, direction * 150);
        this->_sprite->runAction(moveBy);
    }
    else
    {
        auto moveRight = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(150, 0));
        auto moveLeft = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(-150, 0));
        auto moveUp = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(0, 150));
        auto moveDown = cocos2d::MoveBy::create(1.0f, cocos2d::Vec2(0, -150));
        auto pause = cocos2d::DelayTime::create(1.0f);
        auto spawnAction1 = cocos2d::Spawn::createWithTwoActions(moveDown, moveLeft);
        auto spawnAction2 = cocos2d::Spawn::createWithTwoActions(moveDown, moveRight);
        auto spawnAction3 = cocos2d::Spawn::createWithTwoActions(moveUp, moveLeft);
        auto spawnAction4 = cocos2d::Spawn::createWithTwoActions(moveUp, moveRight);
        int times = rand() % 3 + 1;
        int direction = rand() % 7 + 1;
        //for(int i = times; i > 0; i++)
        {
            switch (direction)
            {
                case 1 :
                    this->_sprite->runAction(moveRight);
                    this->_sprite->setFlippedX(true);
                    break;
                case 2 :
                    this->_sprite->runAction(moveLeft);
                    this->_sprite->setFlippedX(false);
                    break;
                case 3 : this->_sprite->runAction(moveUp);
                    break;
                case 4 : this->_sprite->runAction(moveDown);
                    break;
                case 5 :
                    this->_sprite->runAction(spawnAction1);
                    this->_sprite->setFlippedX(false);
                    break;
                case 6 :
                    this->_sprite->runAction(spawnAction2);
                    this->_sprite->setFlippedX(true);
                    break;
                case 7 :
                    this->_sprite->runAction(spawnAction3);
                    this->_sprite->setFlippedX(false);
                    break;
                case 8 :
                    this->_sprite->runAction(spawnAction4);
                    this->_sprite->setFlippedX(true);
                    break;
                default:
                    break;
            }
        }
        
    }
}
void Monster::autoShoot(Vec2 destination)
{
    if(this->isDead())
        return;
    else
    {
        
        this->_sprite->stopAllActions();
        this->_sprite->setOpacity(255);
        //float delayRate = rand() % 3 + 1;
        //float delayTime = DelayTime::create();
        auto originPlace = this->_sprite->getPosition();
        auto direction = Vec2(20 * (destination.x - originPlace.x), 20 * (destination.y - originPlace.y));
        direction.normalize();
        auto rotateAngle = atan(direction.y / direction.x) / 3.14 * 180;
        rotateAngle = direction.x > 0 ? rotateAngle : rotateAngle + 180;
        //log("%lf", rotateAngle);
        auto bullet = Sprite::create(_bulletName);
        bullet->setTag(this->getATK() + 700);
        bullet->setRotation(-rotateAngle);
        bullet->setPosition(originPlace);
        
        auto physicbody = cocos2d::PhysicsBody::createBox(bullet->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicbody->setDynamic(false);
        physicbody->setCategoryBitmask(8);
        physicbody->setContactTestBitmask(1);
        bullet->setPhysicsBody(physicbody);
        
        this->_sprite->getParent()->addChild(bullet, 1);
        
        auto moveBy = cocos2d::MoveBy::create(10.0f, direction * 1000);
        auto removeSelf = RemoveSelf::create();
        bullet->runAction(Sequence::create(moveBy, removeSelf, nullptr));
    }
    
}
void Monster::setCloseMstr()//将怪物设置为近程怪物
{
    auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody->setDynamic(false);
    physicbody->setCategoryBitmask(88);
    physicbody->setContactTestBitmask(98);
    this->_sprite->setPhysicsBody(physicbody);
}

void Monster::setRemoteMstr()
{
    auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
    physicbody->setDynamic(false);
    physicbody->setCategoryBitmask(83);
    physicbody->setContactTestBitmask(108);
    _sprite->setPhysicsBody(physicbody);
}
void Monster::oncontactBegin(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA && nodeB)
    {
        auto posA = nodeA->getPosition();
        auto posB = nodeB->getPosition();
        
        if(posA == this->_sprite->getPosition() || posB == this->_sprite->getPosition())
        {
            if(nodeA->getTag() > 800 && nodeA->getTag() < 900 && nodeB->getTag() >= 10 && nodeB->getTag() <= 13)
            {
                getShot(nodeB->getTag());
            }
            if(nodeB->getTag() > 800 && nodeB->getTag() < 900 && nodeA->getTag() >= 10 && nodeA->getTag() <= 13)
            {
                getShot(nodeA->getTag());
            }
            if(nodeB->getTag() > 800 && nodeB->getTag() < 900 && nodeA->getTag() > 800 && nodeA->getTag() < 900)
            {
                auto direct1 = nodeB->getPosition()-nodeA->getPosition();
                direct1.normalize();
                auto direct2 = nodeA->getPosition()-nodeB->getPosition();
                direct2.normalize();
                auto moveBy1 = MoveBy::create(0.5f, direct1 * 10);
                auto moveBy2 = MoveBy::create(0.5f, direct2 * 10);
                nodeA->runAction(moveBy2);
                nodeB->runAction(moveBy1);
            }
        }
    }
}

void Monster::getShot(int value)//怪物的掉血
{
    if(blood == 0)
        return;
    int bloodReduce = parameter[value].getparameter1();
  //  int bloodReduce = value;
    this->blood = blood - bloodReduce > 0 ? blood - bloodReduce : 0;
    auto fadeIn = FadeIn::create(0.1f);
    auto fadeOut = FadeOut::create(0.1f);
    auto fadeTo = FadeTo::create(0.2f, 1);
    this->_sprite->setOpacity(255);
    this->_sprite->runAction(Sequence::create(fadeOut, fadeIn, nullptr));
    char temp[5];
    sprintf(temp, "%d", bloodReduce);
    auto label = Label::createWithTTF(temp, "fonts/Marker Felt.ttf", 20);
    label->setColor(Color3B::RED);
    label->setPosition(this->_sprite->getPosition());
    this->_sprite->getParent()->addChild(label, 1);
    auto moveDown = MoveBy::create(0.2f, Vec2(0, -20));
    auto removeSelf = RemoveSelf::create();
    label->runAction(Sequence::create(moveDown, fadeOut->clone(), removeSelf, nullptr));
    if(this->blood == 0)
    {
        this->setDead();
        //mstrNum--;
        return;
    }
}

void Monster::setDead(float dt)//怪物死亡
{
    
    auto position = this->_sprite->getPosition();
    this->_sprite->setPosition(position);

    auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicbody->setDynamic(false);
    physicbody->setCategoryBitmask(0);
    physicbody->setContactTestBitmask(0);
    //this->_sprite->setPhysicsBody(physicbody);
    this->_sprite->setTag(2000);
    this->_sprite->setOpacity(255);
    this->_sprite->stopAllActions();
    
    auto rotateBy = RotateBy::create(1.0f, 90.0f);
    auto fadeOut = FadeOut::create(2.0f);
    this->_sprite->runAction(Sequence::create(Spawn::create(rotateBy, fadeOut, nullptr), nullptr));
    
    //this->_sprite->setPosition(Vec2(480, 320));
    mstrNum--;
    
}
