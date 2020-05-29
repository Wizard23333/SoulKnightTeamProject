#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"

//武器类
class Weapon :public Props {
protected:
	//子弹类型
	Bullet use_bullet;
public:
	//武器构造函数
	Weapon(const char* pngName);
	bool powerBullet(cocos2d::Sprite* bullet, cocos2d::Touch* touch);
};

#endif