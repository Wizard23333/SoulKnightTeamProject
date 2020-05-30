#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"

//ҩˮ��
class Potion :public Props {
protected:
	//ҩˮ����
	int blood;
	int energy;
public:
	//ҩˮ���캯��
	Potion(const std::string pngName);
	Potion(const std::string pngName, Node* Box);
	//�������ú���
	void setblood(int _blood);
	void setenergy(int _energy);
	//���Ի�ȡ����
	void Getblood() { return this->blood };
	void Getenergy() { return this->energy };
	//ҩˮ��ײ����
	bool onContactBegin(cocos2d::PhysicsContact& contact)
};

#endif
