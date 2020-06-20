
#ifndef __SAVEMAP_SCENE_H__
#define __SAVEMAP_SCENE_H__

#include "cocos2d.h"
#include <map>
#include "Hero.h"

class SaveMap:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);

	// implement the "static create()" method manually
	CREATE_FUNC(SaveMap);
private:
    Hero myHero;
};

#endif // __SAVEMAP_SCENE_H__
