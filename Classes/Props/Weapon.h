#ifndef WEAPON_H
#define WEAPON_H

#include"cocos2d.h"
#include"Bullet.h"
#include"Props.h"

//武器类
class Weapon :public Props {
public:
	//子弹类型
	int tagofbullet;
	//武器构造函数
	//Weapon(const std::string pngName="HelloWorld.png");
    Weapon(const std::string pngName = "HelloWorld.png", int tag = 5);
	//发射子弹
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//获取子弹消耗的能量
	int GetBulletenergycost() { return parameter[tagofbullet].getparameter2(); };
	//恢复武器透明度
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	//修改子弹类型
	void changeTagofbullet() { this->tagofbullet = 5+this->_sprite->getTag(); };

};

#endif
