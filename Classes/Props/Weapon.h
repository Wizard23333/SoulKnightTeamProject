#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"

//������
class Weapon :public Props {
protected:
	//�ӵ�����
	Bullet bullet;
public:
	//�������캯��
	Weapon(const std::string pngName,Bullet _bullet);
	//��ȡ�ӵ����ĵ�����
	int GetBulletenergycost() { return this->bullet.costenergy; };

};

#endif