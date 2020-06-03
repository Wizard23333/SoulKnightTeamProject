#include"cocos2d.h"
#include"Props.h"
#include"Potion.h"

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
bool Potion::onContactpresolve(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag()>=100||nodeB->getTag()>=100)
	{
		if (nodeA->getTag() == tag_of_the_hero)//英雄的标记
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == tag_of_the_hero)//英雄的标记
		{
			nodeA->removeFromParentAndCleanup(true);
		}
	}
	return true;
}

//药水使用
bool Potion::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T)
	{
		auto temptag = 100 + this->_sprite->getTag();
		this->_sprite->setTag(temptag);
	}
	return true;
}

bool Potion::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode)
{
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T)
	{
		auto temptag = -100 + this->_sprite->getTag();
		this->_sprite->setTag(temptag);
	}
	return true;
}