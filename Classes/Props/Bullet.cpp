#include"Props.h"
#include"Bullet.h"
#include"cocos2d.h"
USING_NS_CC;

//创建子弹
Bullet::Bullet(const std::string pngName):Props(pngName) {
	//设置标记(在场景中修改tag)
	this->_sprite->setTag(10);
	_sprite->setAnchorPoint(Vec2(0, 0));
}


//修改属性
void Bullet::setattack(int _attack) {
    (this->attack) = _attack;
}

void Bullet::setcostenergy(int _costenergy) {
	(this->costenergy) = _costenergy;
}

void Bullet::setknock(int _knock) {
	(this->knock) = _knock;
}

void Bullet::setaccurate(int _accurate) {
	(this->accurate) = _accurate;
}


//子弹射中怪
bool Bullet::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == 10)
	{
		nodeB->removeFromParentAndCleanup(true);
	}
	else if (nodeB->getTag() == 10)
	{
		nodeA->removeFromParentAndCleanup(true);
	}

	return true;
}
