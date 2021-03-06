
#include "SaveMapScene.h"
#include <map>
#include "Hero.h"

USING_NS_CC;
#define GET_TILE_WIDTH tileMap->getTileSize().width
#define GET_TILE_HEIGHT tileMap->getTileSize().height
#define WIN_WIDTH (Director::getInstance()->getWinSize().width)
#define WIN_HEIGHT (Director::getInstance()->getWinSize().height)
#define MAP_WIDTH (tileMap->getTileSize().width * tileMap->getMapSize().width)
#define MAP_HEIGHT (tileMap->getTileSize().height * tileMap->getMapSize().height)

Scene* SaveMap::createScene()
{
    Scene *scene = SaveMap::create();
    SaveMap *layer = SaveMap::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SaveMap::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //物理引擎初始化检测 
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //加入安全地图 
    tileMap = TMXTiledMap::create("basement.tmx");
    tileMap->setScale(0.5);
    this->addChild(tileMap);
    
    
    Point anchorPos = tileMap->getAnchorPoint();
    Point mapPos = tileMap->getPosition();
    
    
    //获取对象层 
    TMXObjectGroup* objectGroup = tileMap->getObjectGroup("knight");


	//进入冒险地图 
    auto enterInfo = objectGroup->getObject("enterAdventure");
    int enterX = enterInfo.at("x").asFloat()+80;
    int enterY = enterInfo.at("y").asFloat()+90;
    
    auto enter = Sprite::create("EnterGame.png");
    enter->setPosition(enterX, enterY);
    enter->setScale(0.65);
    enter->setTag(1001);
    tileMap->addChild(enter, 1);
    
    
    //放置英雄 
    auto knightInfo = objectGroup->getObject("knightBirthPoint");
    int knightX = knightInfo.at("x").asFloat();
    int knightY = knightInfo.at("y").asFloat();
    myHero = Hero("Knight.png");
    myHero._sprite->setPosition(knightX, knightY);
    myHero._sprite->setScale(0.2);
    myHero.setWeapon(5);
    myHero._weapon._sprite->setPosition(myHero._sprite->getPosition());
    myHero._weapon._sprite->setScale(0.10);
    tileMap->addChild(myHero._sprite, 1);
    tileMap->addChild(myHero._weapon._sprite, 2);


	//放置怪物 
    auto monster1Info = objectGroup->getObject("monster1");
    int monster1X = monster1Info.at("x").asFloat()+50;
    int monster1Y = monster1Info.at("y").asFloat()+50;
    auto monster1 = Sprite::create("monster1.png");
    monster1->setPosition(monster1X, monster1Y);
    monster1->setScale(2);
    tileMap->addChild(monster1, 1);

    auto monster2Info = objectGroup->getObject("monster2");
    int monster2X = monster2Info.at("x").asFloat()+40;
    int monster2Y = monster2Info.at("y").asFloat()+50;
    auto monster2 = Sprite::create("monster2.png");
    monster2->setPosition(monster2X, monster2Y);
    monster2->setScale(1.8);
    tileMap->addChild(monster2, 1);

    auto monster3Info = objectGroup->getObject("monster3");
    int monster3X = monster3Info.at("x").asFloat()+40;
    int monster3Y = monster3Info.at("y").asFloat()+50;
    auto monster3 = Sprite::create("monster3.png");
    monster3->setPosition(monster3X, monster3Y);
    monster3->setScale(1.8);
    tileMap->addChild(monster3, 1);

    auto monster4Info = objectGroup->getObject("monster4");
    int monster4X = monster4Info.at("x").asFloat() + 45;
    int monster4Y = monster4Info.at("y").asFloat() + 50;
    auto monster4 = Sprite::create("monster4.png");
    monster4->setPosition(monster4X, monster4Y);
    monster4->setScale(1.7);
    tileMap->addChild(monster4, 1);

    auto monster5Info = objectGroup->getObject("monster5");
    int monster5X = monster5Info.at("x").asFloat() + 40;
    int monster5Y = monster5Info.at("y").asFloat() + 50;
    auto monster5 = Sprite::create("monster5.png");
    monster5->setPosition(monster5X, monster5Y);
    monster5->setScale(1.8);
    tileMap->addChild(monster5, 1);

    
    //放置武器 
    auto weapon1Info = objectGroup->getObject("weapon1");
    int weapon1X = weapon1Info.at("x").asFloat() + 40;
    int weapon1Y = weapon1Info.at("y").asFloat() + 50;
    auto weapon1 = Sprite::create("Sickle.png");
    weapon1->setPosition(weapon1X, weapon1Y);
    weapon1->setScale(0.1);
    tileMap->addChild(weapon1, 1);
    
    auto weapon2Info = objectGroup->getObject("weapon2");
    int weapon2X = weapon2Info.at("x").asFloat() + 40;
    int weapon2Y = weapon2Info.at("y").asFloat() + 50;
    auto weapon2 = Sprite::create("Sword.png");
    weapon2->setPosition(weapon2X, weapon2Y);
    weapon2->setScale(0.2);
    tileMap->addChild(weapon2, 1);
    
    auto weapon3Info = objectGroup->getObject("weapon3");
    int weapon3X = weapon3Info.at("x").asFloat() + 40;
    int weapon3Y = weapon3Info.at("y").asFloat() + 50;
    auto weapon3 = Sprite::create("Darts.png");
    weapon3->setPosition(weapon3X, weapon3Y);
    weapon3->setScale(0.3);
    tileMap->addChild(weapon3,1);

    auto weapon4Info = objectGroup->getObject("weapon4");
    int weapon4X = weapon4Info.at("x").asFloat() + 40;
    int weapon4Y = weapon4Info.at("y").asFloat() + 50;
    auto weapon4 = Sprite::create("Gun.png");
    weapon4->setPosition(weapon4X, weapon4Y);
    weapon4->setScale(0.15);
    tileMap->addChild(weapon4, 1);
    
    
    this->scheduleUpdate();
    
    //键盘事件监听 
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(SaveMap::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(SaveMap::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    return true;
}


void SaveMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


void SaveMap::update(float delta)
{
    updateMap();
    updateHeroAction();
}

//地图随人物移动，基本保持人物处于窗口中心 
void SaveMap::updateMap()
{
	//hero位置 
    Point orig = myHero._sprite->getPosition();
    //窗口中心位置 
    Point dest = Vec2(WIN_WIDTH / 2 + 450, WIN_HEIGHT);
    //相对位置差 
    Point distance = dest - orig; 
    Point mapPos = Vec2(0, 0) + distance * 0.5;
    //防止窗口显示超出地图范围 
    mapPos.x = (mapPos.x > 0 ? 0 : mapPos.x);
    mapPos.y = (mapPos.y > 0 ? 0 : mapPos.y);
    mapPos.x = (mapPos.x < WIN_WIDTH - MAP_WIDTH / 2  ? WIN_WIDTH - MAP_WIDTH / 2 : mapPos.x);
    mapPos.y = (mapPos.y < WIN_HEIGHT - MAP_HEIGHT ? WIN_WIDTH - MAP_WIDTH : mapPos.y);
    tileMap->setPosition(mapPos);

}

//碰撞控制 
void SaveMap::updateHeroAction()
{
    auto pos = myHero._sprite->getPosition();
    Point heroPos = cocoscoord2tilemapcoord(pos);
    if(heroPos.x >= 31 && heroPos.x < 34)
    {
        if(heroPos.y < 6)
        {
            log("hero%f %f", heroPos.x, heroPos.y);

            Director::getInstance()->replaceScene(FightGround::createScene());
    
        }
    }
    //获取地图中碰撞层 
    auto collision = tileMap->getLayer("collision");
    if (collision->getTileGIDAt(heroPos))
    {
        if(heroPos.x > 66)
        {
        myHero._sprite->stopAllActions();
        myHero._sprite->setPosition(Vec2(myHero._sprite->getPosition().x - 10, myHero._sprite->getPosition().y));
        }
        if(heroPos.x < 1)
        {
            myHero._sprite->stopAllActions();
            myHero._sprite->setPosition(Vec2(myHero._sprite->getPosition().x + 10, myHero._sprite->getPosition().y));
        }
        if(heroPos.y < 7)
        {
            myHero._sprite->stopAllActions();
            myHero._sprite->setPosition(Vec2(myHero._sprite->getPosition().x, myHero._sprite->getPosition().y - 10));
        }
        if(heroPos.y > 12)
        {
            myHero._sprite->stopAllActions();
            myHero._sprite->setPosition(Vec2(myHero._sprite->getPosition().x, myHero._sprite->getPosition().y + 10));
        }
        
    }
}

//将cocos坐标转换为map坐标 
Point SaveMap::tileCoordForPosition(Point pos)
{
    Point coord;
    coord.x = pos.x / GET_TILE_WIDTH;
    coord.y = (MAP_HEIGHT - pos.y) / GET_TILE_HEIGHT;
    return coord;
}

//按键按下的回调 
bool  SaveMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	//成员函数处理键盘信息
    myHero.onKeyPressed(keycode);
    return true;
}

bool SaveMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    myHero.onKeyRelesed(keycode);
    return true;
}


void SaveMap::nextScene(float dt)
{
    auto pos = myHero._sprite->getPosition();
    Point heroPos = cocoscoord2tilemapcoord(pos);
    log("hero%f %f", heroPos.x, heroPos.y);
}






