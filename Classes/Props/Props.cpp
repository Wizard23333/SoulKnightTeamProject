#include"Props.h"

USING_NS_CC;
//��������

Props::Props(const std::string pngName, Node* Box) {
	//�����λ�ô������ߣ��ɸ�Ϊ�ڱ���λ�ã�
	_sprite = Sprite::create(pngName);
	_sprite->setPosition(Box->getPosition());

	//��ӵ��ߵ�����ģ��
	auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_sprite->setPhysicsBody(physicsBody);
}
Props::Props(const std::string pngName)
{
    _sprite = Sprite::create(pngName);
    auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(4);
    physicsBody->setContactTestBitmask(2);
    _sprite->setPhysicsBody(physicsBody);
}


