#include"Props.h"
#include"Bullet.h"
#include"cocos2d.h"
USING_NS_CC;

//�����ӵ�
Bullet::Bullet(const std::string pngName):Props(pngName) {
	//���ñ��(�ڳ������޸�tag)
	this->_sprite->setTag(10);
	_sprite->setAnchorPoint(Vec2(0, 0));
}


//�޸�����
void Bullet::setattack(int _attack) {
    (this->attack) = _attack;
}

void Bullet::setcostenergy(int _costenergy) {
	(this->costenergy) = _costenergy;
}

void Bullet::setknock(int _knock) {
	(this->knock) = _knock;
}

void Bullet::setaccurate(int _accurate) {
	(this->accurate) = _accurate;
}


//�ӵ����й�
bool Bullet::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == 10)
	{
		nodeB->removeFromParentAndCleanup(true);
	}
	else if (nodeB->getTag() == 10)
	{
		nodeA->removeFromParentAndCleanup(true);
	}

	return true;
}
