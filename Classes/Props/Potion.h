#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"

//药水类
class Potion :public Props {
protected:
	//药水属性
	int blood;
	int energy;
public:
	//药水构造函数
	Potion(const std::string pngName);
	Potion(const std::string pngName, Node* Box);
	//属性设置函数
	void setblood(int _blood);
	void setenergy(int _energy);
	//属性获取函数
	void Getblood() { return this->blood };
	void Getenergy() { return this->energy };
	//药水碰撞函数
	bool onContactBegin(cocos2d::PhysicsContact& contact)
};

#endif
