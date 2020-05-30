#ifndef BULLET_H
#define BULLET_H

#include"cocos2d.h"

//子弹类
class Bullet :public Props {
protected:
	//子弹属性
	int attack;
	int costenergy;
	int knock;
	int accurate;
public:
	//子弹构造函数(附带属性)
	Bullet(const std::string pngName, int attack, int conenergy, int knock, int accurate);
	//子弹构造函数(不附带属性)
	Bullet(const std::string pngName);
	//发射子弹
	bool onTouchBegan(Touch* touch, Event* unused_event);
	//子弹射中
	bool onContactBegin(cocos2d::PhysicsContact& contact)
	//设置属性
	void setattack(int _attack);
	void setcostenergy(int _costenergy);
	void setknock(int _knock);
	void setaccurate(int _accurate);
};

#endif
