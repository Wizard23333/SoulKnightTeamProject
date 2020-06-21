
#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    //enter game 
	void menuStartCallBack(cocos2d::Ref* pSender);
	//control music 
	void menuCloseMusic(cocos2d::Ref* pSender);

    CREATE_FUNC(Welcome);
};

#endif // __WELCOME_SCENE_H__
