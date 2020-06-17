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
	//Weapon(const std::string pngName="HelloWorld.png");
    Weapon(const std::string pngName = "HelloWorld.png", int tag = 5);
	//�����ӵ�
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//��ȡ�ӵ����ĵ�����
	int GetBulletenergycost() { return parameter[tagofbullet].getparameter2(); };
	//�ָ�����͸����
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//�޸��ӵ�����
	void changeTagofbullet() { this->tagofbullet = 5+this->_sprite->getTag(); };

};

#endif
