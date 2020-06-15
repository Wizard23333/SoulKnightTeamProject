
#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallBack(cocos2d::Ref* pSender);
	void menuCloseMusic(cocos2d::Ref* pSender);
	void menuCloseEffect(Ref* pSender);
    //add
    bool isMusicPlaying;
    // implement the "static create()" method manually
    CREATE_FUNC(Welcome);
};

#endif // __WELCOME_SCENE_H__
