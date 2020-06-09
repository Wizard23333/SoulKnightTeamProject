#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"
#include"Props.h"
USING_NS_CC;
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
    int Getblood() { return this->blood; };
    int Getenergy() { return this->energy; };
	//ҩˮ��ײ����
	bool onContactpresolve(cocos2d::PhysicsContact& contact);
	//ҩˮʹ�ú���
	bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode);
};

#endif
