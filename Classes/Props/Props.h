/* Props.h */
#ifndef PROPS_H
#define PROPS_H

#include"cocos2d.h"
//道具基类
class Props {
protected:
	cocos2d::Sprite* _sprite;
public:
	//道具构造函数
	//1.默认位置Hero处
	Props(const char* pngName);
	//2.指定位置处
	Props(const char* pngName, Node* Box);
	//是否与英雄碰撞
	bool onContactWithHero(cocos2d::Node* Hero);
};

#endif
