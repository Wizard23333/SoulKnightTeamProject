#include "Monster.h"
Monster::Monster(const std::string pngName, int Blood, int atk)
:blood(Blood), Actor(pngName), ATK(atk)
{
    _bulletSprite->create("Bullet.png");
}

Monster * Monster::monsterCreate(const std::string pngName, int Blood, int atk)
{
    actorCreate(pngName);
    blood = Blood;
    ATK = atk;
    _bulletSprite->create("Bullet.png");
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

void Monster::autoMove()
{
    if(this->isDead())
        return;
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
                case 1 : this->_sprite->runAction(moveRight);
                    break;
                case 2 : this->_sprite->runAction(moveLeft);
                    break;
                case 3 : this->_sprite->runAction(moveUp);
                    break;
                case 4 : this->_sprite->runAction(moveDown);
                    break;
                case 5 : this->_sprite->runAction(spawnAction1);
                    break;
                case 6 : this->_sprite->runAction(spawnAction2);
                    break;
                case 7 : this->_sprite->runAction(spawnAction3);
                    break;
                case 8 : this->_sprite->runAction(spawnAction4);
                    break;
                default:
                    break;
            }
        }
        
        
        
        
    }
}
