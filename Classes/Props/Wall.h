#ifndef WALL_H
#define WALL_H

#include"cocos2d.h"
#include"Props.h"
USING_NS_CC;
//ǽ����
class Wall :public Props {
public:
	//ǽ�幹�캯��
	Wall(const std::string pngName = "HelloWorld.png");
	//��������Χǽ
	void createWall(double width,double height);
};

#endif
