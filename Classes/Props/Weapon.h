#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"

//������
class Weapon :public Props {
protected:
	//�ӵ�����
	Bullet use_bullet;
public:
	//�������캯��
	Weapon(const char* pngName);
	bool powerBullet(cocos2d::Sprite* bullet, cocos2d::Touch* touch);
};

#endif