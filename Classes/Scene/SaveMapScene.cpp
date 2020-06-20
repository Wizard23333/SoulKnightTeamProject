
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
	//tileMap->setPosition(-820, 0);
	

	

	TMXObjectGroup* objectGroup = tileMap->getObjectGroup("knight");

	auto knightInfo = objectGroup->getObject("knightBirthPoint");
	int knightX = knightInfo.at("x").asFloat();
	int knightY = knightInfo.at("y").asFloat();
	auto knight = Sprite::create("knight.png");
	knight->setPosition(knightX,knightY);
	knight->setScale(0.3);
	tileMap->addChild(knight, 2);

	auto enterInfo = objectGroup->getObject("enterAdventure");
	int enterX = enterInfo.at("x").asFloat()+80;
	int enterY = enterInfo.at("y").asFloat()+90;
	auto enter = Sprite::create("EnterGame.png");
	enter->setPosition(enterX, enterY);
	enter->setScale(0.65);
	tileMap->addChild(enter, 1);

	auto monster1Info = objectGroup->getObject("monster1");
	int monster1X = monster1Info.at("x").asFloat()+50;
	int monster1Y = monster1Info.at("y").asFloat()+50;
	auto monster1 = Sprite::create("enemies/monster1.png");
	monster1->setPosition(monster1X, monster1Y);
	monster1->setScale(2);
	tileMap->addChild(monster1, 1);

	auto monster2Info = objectGroup->getObject("monster2");
	int monster2X = monster2Info.at("x").asFloat()+40;
	int monster2Y = monster2Info.at("y").asFloat()+50;
	auto monster2 = Sprite::create("enemies/monster2.png");
	monster2->setPosition(monster2X, monster2Y);
	monster2->setScale(1.8);
	tileMap->addChild(monster2, 1);

	auto monster3Info = objectGroup->getObject("monster3");
	int monster3X = monster3Info.at("x").asFloat()+40;
	int monster3Y = monster3Info.at("y").asFloat()+50;
	auto monster3 = Sprite::create("enemies/monster3.png");
	monster3->setPosition(monster3X, monster3Y);
	monster3->setScale(1.8);
	tileMap->addChild(monster3, 1);

	auto monster4Info = objectGroup->getObject("monster4");
	int monster4X = monster4Info.at("x").asFloat() + 45;
	int monster4Y = monster4Info.at("y").asFloat() + 50;
	auto monster4 = Sprite::create("enemies/monster4.png");
	monster4->setPosition(monster4X, monster4Y);
	monster4->setScale(1.7);
	tileMap->addChild(monster4, 1);

	auto monster5Info = objectGroup->getObject("monster5");
	int monster5X = monster5Info.at("x").asFloat() + 40;
	int monster5Y = monster5Info.at("y").asFloat() + 50;
	auto monster5 = Sprite::create("enemies/monster5.png");
	monster5->setPosition(monster5X, monster5Y);
	monster5->setScale(1.8);
	tileMap->addChild(monster5, 1);

	this->addChild(tileMap, 0);
	
	auto weapon1Info = objectGroup->getObject("weapon1");
	int weapon1X = weapon1Info.at("x").asFloat() + 40;
	int weapon1Y = weapon1Info.at("y").asFloat() + 50;
	auto weapon1 = Sprite::create("weapons/close-in weapons/Sickle.png");
	weapon1->setPosition(weapon1X, weapon1Y);
	weapon1->setScale(0.1);
	tileMap->addChild(weapon1, 1);
	
	auto weapon2Info = objectGroup->getObject("weapon2");
	int weapon2X = weapon2Info.at("x").asFloat() + 40;
	int weapon2Y = weapon2Info.at("y").asFloat() + 50;
	auto weapon2 = Sprite::create("weapons/close-in weapons/sword.png");
	weapon2->setPosition(weapon2X, weapon2Y);
	weapon2->setScale(0.2);
	tileMap->addChild(weapon2, 2);
	
	auto weapon3Info = objectGroup->getObject("weapon3");
	int weapon3X = weapon3Info.at("x").asFloat() + 40;
	int weapon3Y = weapon3Info.at("y").asFloat() + 50;
	auto weapon3 = Sprite::create("weapons/ranged weapons/Darts.png");
	weapon3->setPosition(weapon3X, weapon3Y);
	weapon3->setScale(0.3);
	tileMap->addChild(weapon3, 3);

	auto weapon4Info = objectGroup->getObject("weapon4");
	int weapon4X = weapon4Info.at("x").asFloat() + 40;
	int weapon4Y = weapon4Info.at("y").asFloat() + 50;
	auto weapon4 = Sprite::create("weapons/ranged weapons/Gun.png");
	weapon4->setPosition(weapon4X, weapon4Y);
	weapon4->setScale(0.15);
	tileMap->addChild(weapon4, 4);
	
	
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
