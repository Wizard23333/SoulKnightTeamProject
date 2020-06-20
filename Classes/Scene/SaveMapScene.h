
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
	void menuCloseCallback(cocos2d::Ref* pSender);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	bool onContactBegan(cocos2d::PhysicsContact &);
	bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	CREATE_FUNC(SaveMap);
	void mapUpdate(Point kinght);

private:
	Hero myHero;
	void setMapPosForView(Point playerPos);
    void update(float delta);
	void updateMap();
	TMXTiledMap *tileMap;
	Point cocoscoord2tilemapcoord(Point pos);
	void isCollide();

};

#endif // __SAVEMAP_SCENE_H__
