#include"Props.h"

USING_NS_CC;

//��������
Weapon::Weapon(const std::string pngName, Bullet _bullet)
{
	Props(pngName);
	_sprite->setTag(15);
	this->bullet = _bullet;
};
