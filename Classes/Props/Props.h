/* Props.h */
//统一一下
//药水标记数字0-4
//武器标记数字5-9
//子弹标记数字10-14
#ifndef PROPS_H
#define PROPS_H
#include<iostream>
#include"cocos2d.h"
using namespace std;
USING_NS_CC;
//各类道具属性常量
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
	//获取道具属性的函数
	string getpngname() const{ return pngName; };
	int getparameter1() const{ return parameter1; };
	int getparameter2() const{ return parameter2; };
	int getparameter3() const{ return parameter3; };
	int getparameter4() const{ return parameter4; };
};


const Propsvalue parameter[20] = {
	Propsvalue("pngName1",1,1,1,1),Propsvalue("pngName2",1,1,1,1),Propsvalue("pngName3",1,1,1,1),Propsvalue("pngName4",1,1,1,1),Propsvalue("pngName5",1,1,1,1),
	Propsvalue("pngName6",1,1,1,1),Propsvalue("pngName7",1,1,1,1),Propsvalue("pngName8",1,1,1,1),Propsvalue("pngName9",1,1,1,1),Propsvalue("pngName10",1,1,1,1),
	Propsvalue("pngName11",1,1,1,1),Propsvalue("pngName12",1,1,1,1),Propsvalue("pngName13",1,1,1,1),Propsvalue("pngName14",1,1,1,1),Propsvalue("pngName15",1,1,1,1),
	Propsvalue("pngName16",1,1,1,1),Propsvalue("pngName17",1,1,1,1),Propsvalue("pngName18",1,1,1,1),Propsvalue("pngName19",1,1,1,1),Propsvalue("pngName20",1,1,1,1),
};

//道具基类
class Props {
protected:
	cocos2d::Sprite* _sprite;
public:
	//道具构造函数
	Props(const std::string pngName, Node* Box);
};

#endif
