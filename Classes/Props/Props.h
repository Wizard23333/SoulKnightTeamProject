/* Props.h */
//统一一下
//药水标记数字0-4
//武器标记数字5-9
//子弹标记数字10-14
#ifndef PROPS_H
#define PROPS_H

#include"cocos2d.h"
//各类道具属性常量
const int number[20][5] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
}

//道具基类
class Props {
protected:
	cocos2d::Sprite* _sprite;
public:
	//道具构造函数
	//1.默认位置Hero处
	Props(const std::string pngName);
	//2.指定位置处
	Props(const std::string pngName, Node* Box);
};

#endif
