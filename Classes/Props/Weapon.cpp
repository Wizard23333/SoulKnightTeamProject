#include"Props.h"

USING_NS_CC;

//´´½¨ÎäÆ÷
Weapon::Weapon(const std::string pngName, Bullet _bullet)
{
	Props(pngName);
	_sprite->setTag(15);
	this->bullet = _bullet;
};

void Weapon::ChangeWeapon(Weapon weapon) {
	auto nodeA = weapon->getBody()->getNode();
	int tagA = weapon._sprite->getTag();

	nodeA->removeFromParentAndCleanup(true);
}