#include"Props.h"

USING_NS_CC;
//道具生成
Props::Props(const std::string pngName) {
	//在玩家位置创建道具
	_sprite = Sprite::create("pngName.png");
	_sprite->setPosition(_player->getPosition());
	
	//添加道具的物理模型
	auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_sprite->setPhysicsBody(physicsBody);
}

Props::Props(const std::string pngName, Node* Box) {
	//在玩家位置创建道具（可改为在宝箱位置）
	_sprite = Sprite::create("pngName.png");
	_sprite->setPosition(Box->getPosition());

	//添加道具的物理模型
	auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_sprite->setPhysicsBody(physicsBody);
}



