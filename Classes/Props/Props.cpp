#include"Props.h"

USING_NS_CC;
//道具生成

Props::Props(const std::string name)
{
    this->_sprite = cocos2d::Sprite::create(name);
    auto physicsBody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(3);
    physicsBody->setContactTestBitmask(12);
    this->_sprite->setPhysicsBody(physicsBody);

}


/*Props* Props::propsCreate(const std::string name)
{
	_sprite = cocos2d::Sprite::create(name);
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(3);
	physicsBody->setContactTestBitmask(12);
	this->_sprite->setPhysicsBody(physicsBody);
	return this;
}*/

