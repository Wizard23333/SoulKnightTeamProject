#include"cocos2d.h"
#include"Props.h"
#include"Bullet.h"
USING_NS_CC;

//´´½¨ÎäÆ÷
Weapon::Weapon(const std::string pngName, Bullet _bullet)
{
	Props(pngName);
	_sprite->setTag(15);
	this->bullet = _bullet;
};
