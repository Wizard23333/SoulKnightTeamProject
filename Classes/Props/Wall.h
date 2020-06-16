#ifndef WALL_H
#define WALL_H

#include"cocos2d.h"
#include"Props.h"
USING_NS_CC;
//墙体类
class Wall :public Props {
public:
	//墙体构造函数
	Wall(const std::string pngName = "HelloWorld.png");
	//构建矩形围墙
	void createWall(double width,double height);
};

#endif
