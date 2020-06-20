#ifndef PauseScene_h
#define PauseScene_h

#include "cocos2d.h"

USING_NS_CC;
class PauseScene:public Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void backGameCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseScene);

    Size visibleSize;
    Vec2 originPoint;
    private:
};

#endif

