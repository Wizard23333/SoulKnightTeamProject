/* Props.h */
#ifndef PROPS_H
#define PROPS_H

#include"cocos2d.h"
//���߻���
class Props {
protected:
	cocos2d::Sprite* _sprite;
public:
	//���߹��캯��
	//1.Ĭ��λ��Hero��
	Props(const char* pngName);
	//2.ָ��λ�ô�
	Props(const char* pngName, Node* Box);
	//�Ƿ���Ӣ����ײ
	bool onContactWithHero(cocos2d::Node* Hero);
};

#endif
