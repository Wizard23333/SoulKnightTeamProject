/* Props.h */
//ͳһһ��
//ҩˮ�������0-4
//�����������5-9
//�ӵ��������10-14
#ifndef PROPS_H
#define PROPS_H
#include<iostream>
#include"cocos2d.h"
using namespace std;
USING_NS_CC;
//����������Գ���
class Propsvalue {
private:
	string pngName;
	int parameter1;
	int parameter2;
	int parameter3;
	int parameter4;
public:
	Propsvalue(string name = "props", int parameter1 = 0, int parameter2 = 0, int parameter3 = 0, int parameter4 = 0)
		:pngName(name), parameter1(parameter1), parameter2(parameter2), parameter3(parameter3), parameter4(parameter4) {};
	~Propsvalue() {};
	//��ȡ�������Եĺ���
	string getpngname() const{ return pngName; };
	int getparameter1() const{ return parameter1; };
	int getparameter2() const{ return parameter2; };
	int getparameter3() const{ return parameter3; };
	int getparameter4() const{ return parameter4; };
};


const Propsvalue parameter[20] = {
	Propsvalue("Blood.png",2,0,0,0),Propsvalue("Energy.png",0,20,0,0),Propsvalue("HelloWorld.png",1,1,0,0),Propsvalue("HelloWorld.png",1,1,0,0),Propsvalue("HelloWorld.png",1,1,0,0),
	Propsvalue("Sickle.png",1,1,1,1),Propsvalue("Sword.png",1,1,1,1),Propsvalue("Darts.png",1,1,1,1),Propsvalue("Gun.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),
	Propsvalue("Sickle.png",1,1,1,1),Propsvalue("Sword.png",1,1,1,1),Propsvalue("Darts.png",1,1,1,1),Propsvalue("Bullet.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),
	Propsvalue("Wall.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),Propsvalue("HelloWorld.png",1,1,1,1),
};
/*
//���߻���
class Props {
protected:
	//
public:
	//���߹��캯��
    cocos2d::Sprite* _sprite;
	Props(const std::string pngName, Node* Box);
};
*/
class Props
{
public:
    cocos2d::Sprite * _sprite;
    Props(const std::string name = "HelloWorld.png");
	//Props* propsCreate(const std::string name = "HelloWorld.png");
 
};
#endif
