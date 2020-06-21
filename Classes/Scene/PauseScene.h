#ifndef PauseScene_h
#define PauseScene_h

#include "cocos2d.h"
USING_NS_CC;
class PauseScene:public Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //返回安全地图回调
    void menuCloseCallback(cocos2d::Ref* pSender);
    //返回游戏场景回调
    void backGameCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseScene);
    Size visibleSize;
    Vec2 originPoint;
    private:
};

#endif

