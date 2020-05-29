#include"Props.h"

USING_NS_CC;

//创建武器
Weapon::Weapon(const char* pngName, Bullet _bullet)
{
	Props(pngName);
	_weapon->setTag(8);
	this->use_bullet = _bullet;
	//添加到场景中
	this->addChild(_sprite);
};

Weapon::bool powerBullet(cocos2d::Sprite* bullet, cocos2d::Touch* touch) {};