#include"Props.h"

USING_NS_CC;
//��������
Props::Props(const std::string name)
{
    _sprite = Sprite::create(name);
    auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(4);
    physicsBody->setContactTestBitmask(2);
    _sprite->setPhysicsBody(physicsBody);
}

/*Props::Props(const std::string pngName, Node* Box) {
	//�����λ�ô������ߣ��ɸ�Ϊ�ڱ���λ�ã�
	_sprite = Sprite::create(pngName);
    auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(4);
    physicsBody->setContactTestBitmask(2);
    _sprite->setPhysicsBody(physicsBody);
}*/
void Props::hideSelf()
{
    auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(0);
    physicsBody->setContactTestBitmask(0);
    _sprite->setPhysicsBody(physicsBody);
    
    _sprite->setOpacity(0);
}

void Props::appearSelf()
{
    if(_sprite == nullptr)
        return;
    auto physicsBody = PhysicsBody::createBox(_sprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(4);
    physicsBody->setContactTestBitmask(2);
    _sprite->setPhysicsBody(physicsBody);
    
    auto fadeIn = FadeIn::create(1.0f);
    _sprite->runAction(fadeIn);
}
