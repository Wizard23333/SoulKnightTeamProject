#include"Props.h"

USING_NS_CC;

//����ҩˮ
Potion::Potion(const char* pngName, int _blood, int _energy, int _sheild,Node*Box) {
	Props(pngName,Box);
	_sprite->setTag(10);
	
	(this->blood) = _blood;
	(this->energy) = _energy;
	(this->sheild) = _sheild;

	//��ӵ�������
	this->addChild(_sprite);
};