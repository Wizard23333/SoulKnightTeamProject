#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"
#include"Bullet.h"
#include"Props.h"

//������
class Weapon :public Props {
public:
	//�ӵ�����
	int tagofbullet;
	//�������캯��
	Weapon(const std::string pngName="HelloWorld.png");
	//�����ӵ�
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//��ȡ�ӵ����ĵ�����
	int GetBulletenergycost() { return parameter[tagofbullet].getparameter2(); };
	//�ָ�����͸����
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	

};

#endif