#include"Props.h"

USING_NS_CC;

//��������
Weapon::Weapon(const char* pngName, Bullet _bullet)
{
	Props(pngName);
	_weapon->setTag(8);
	this->use_bullet = _bullet;
	//��ӵ�������
	this->addChild(_sprite);
};

Weapon::bool powerBullet(cocos2d::Sprite* bullet, cocos2d::Touch* touch) {};