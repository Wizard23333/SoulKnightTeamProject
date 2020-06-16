#include"Props.h"
#include"Wall.h"
#include"cocos2d.h"
USING_NS_CC;

//创建子弹
Wall::Wall(const std::string pngName) :Props(pngName) {
	//设置标记
	this->_sprite->setTag(15);
	auto physicsBody = PhysicsBody::createBox(this->_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(63);
	physicsBody->setContactTestBitmask(63);
	this->_sprite->setPhysicsBody(physicsBody);
}

/*void Wall::createWall(double width,double height)
{
	for (double i = 1; i <= 9;i=i+0.5)
	{
		for (double j = 1; j <= 9;j=j+0.5 )
		{
			if (i > 1 && i < 9 && j>1 && j < 9)
			{
				continue;
			}
			double k1 = 0.1 * i, k2 = 0.1 * j;
			Wall wall = Wall("Wall.png");
			wall._sprite->setPosition(Vec2(winSize.width * k1, winSize.height * k2));
			wall._sprite->setScale(0.10);
			this->addChild(wall._sprite);
		}
	}  
};*/
