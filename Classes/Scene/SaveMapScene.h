
#ifndef __SAVEMAP_SCENE_H__
#define __SAVEMAP_SCENE_H__

#include "cocos2d.h"
#include <map>
#include "Hero.h"
#include "FightGroundScene.h"


class SaveMap:public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
    CREATE_FUNC(SaveMap);

private:
    Hero myHero;
    void setMapPosForView(Point playerPos);
    void update(float delta);
    void updateHeroAction();
    void updateMap();
    TMXTiledMap *tileMap;
    Point tileCoordForPosition(Point pos);
    

};

#endif // __SAVEMAP_SCENE_H__
