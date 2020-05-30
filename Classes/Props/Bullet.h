#ifndef BULLET_H
#define BULLET_H

#include"cocos2d.h"

//�ӵ���
class Bullet :public Props {
protected:
	//�ӵ�����
	int attack;
	int costenergy;
	int knock;
	int accurate;
public:
	//�ӵ����캯��(��������)
	Bullet(const std::string pngName, int attack, int conenergy, int knock, int accurate);
	//�ӵ����캯��(����������)
	Bullet(const std::string pngName);
	//�����ӵ�
	bool onTouchBegan(Touch* touch, Event* unused_event);
	//�ӵ�����
	bool onContactBegin(cocos2d::PhysicsContact& contact)
	//��������
	void setattack(int _attack);
	void setcostenergy(int _costenergy);
	void setknock(int _knock);
	void setaccurate(int _accurate);
};

#endif
