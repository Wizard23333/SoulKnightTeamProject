#ifndef POTION_H
#define POTION_H

#include"cocos2d.h"

//ҩˮ��
class Potion :public Props {
protected:
	//ҩˮ����
	int blood;
	int energy;
	int sheild;
public:
	//ҩˮ���캯��
	Potion(const char* pngName, int blood, int energy, int sheild);
	bool use();
};

#endif
