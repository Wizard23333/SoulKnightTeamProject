#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"

//药水类
class Potion :public Props {
protected:
	//药水属性
	int blood;
	int energy;
	int sheild;
public:
	//药水构造函数
	Potion(const char* pngName, int blood, int energy, int sheild);
	bool use();
};

#endif
