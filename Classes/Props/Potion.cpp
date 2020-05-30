#include"Props.h"

USING_NS_CC;

//在英雄处创建药水
Potion::Potion(const std::string pngName) {
	Props(pngName);
	//设置标记
	_sprite->setTag(10);
}

//在宝箱处创建药水
Potion::Potion(const std::string pngName, Node* Box) {
	Props(pngName,Box);
	//设置标记
	_sprite->setTag(10);
}

//设置属性函数
void Potion::setblood(int _blood) {
	(this->blood) = _blood;
}
void Potion::setenergy(int _energy) {
	(this->energy) = _energy;
}

//药水碰撞函数
bool Potion::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == tag_of_the_hero)//英雄的标记
	{
		nodeB->removeFromParentAndCleanup(true);
	}
	else if (nodeB->getTag() == tag_of_the_hero)//英雄的标记
	{
		nodeA->removeFromParentAndCleanup(true);
	}

	return true;
}