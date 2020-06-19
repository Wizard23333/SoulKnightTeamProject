
#include "SaveMapScene.h"


USING_NS_CC;

Scene* SaveMap::createScene()
{
	return SaveMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SaveMap::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	TMXTiledMap *tileMap = TMXTiledMap::create("map/basement.tmx");
	tileMap->setScale(0.5);
	//tileMap->setPosition(-520, 0);
	this->addChild(tileMap);

	

	TMXObjectGroup* objectGroup = tileMap->getObjectGroup("knight");
	auto knightInfo = objectGroup->getObject("knightBirthPoint");
	int x = knightInfo.at("x").asFloat();
	int y = knightInfo.at("y").asFloat();

	auto knight = Sprite::create("Knight.png");
	knight->setPosition(x, y);
	knight->setScale(0.3);
	tileMap->addChild(knight);
	
	




	return true;
}


void SaveMap::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
