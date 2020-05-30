#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"

//武器类
class Weapon :public Props {
protected:
	//子弹类型
	Bullet bullet;
public:
	//武器构造函数
	Weapon(const std::string pngName);
	//获取子弹消耗的能量
	int GetBulletenergycost() { return this->bullet.costenergy; };
	//交换武器
	void ChangeWeapon(int tag);
};

#endif