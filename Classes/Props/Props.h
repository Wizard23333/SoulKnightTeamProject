/* Props.h */
//ͳһһ��
//ҩˮ�������0-4
//�����������5-9
//�ӵ��������10-14
#ifndef PROPS_H
#define PROPS_H

#include"cocos2d.h"
//����������Գ���
const int number[20][5] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
}

//���߻���
class Props {
protected:
	cocos2d::Sprite* _sprite;
public:
	//���߹��캯��
	//1.Ĭ��λ��Hero��
	Props(const std::string pngName);
	//2.ָ��λ�ô�
	Props(const std::string pngName, Node* Box);
};

#endif
