#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"
#include"Props.h"
USING_NS_CC;
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
    int Getblood() { return this->blood; };
    int Getenergy() { return this->energy; };
	//药水碰撞函数
	bool onContactpresolve(cocos2d::PhysicsContact& contact);
	//药水使用函数
	bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode);
};

#endif
