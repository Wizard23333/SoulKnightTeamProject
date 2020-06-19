
#ifndef __SAVEMAP_SCENE_H__
#define __SAVEMAP_SCENE_H__

#include "cocos2d.h"
#include <map>


class SaveMap:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SaveMap);
};

#endif // __SAVEMAP_SCENE_H__
