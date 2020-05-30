#include"Props.h"

USING_NS_CC;
//��������
Props::Props(const std::string pngName) {
	//�����λ�ô�������
	_sprite = Sprite::create("pngName.png");
	_sprite->setPosition(_player->getPosition());
	
	//��ӵ��ߵ�����ģ��
	auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_sprite->setPhysicsBody(physicsBody);
}

Props::Props(const std::string pngName, Node* Box) {
	//�����λ�ô������ߣ��ɸ�Ϊ�ڱ���λ�ã�
	_sprite = Sprite::create("pngName.png");
	_sprite->setPosition(Box->getPosition());

	//��ӵ��ߵ�����ģ��
	auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_sprite->setPhysicsBody(physicsBody);
}



