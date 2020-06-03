#include"Props.h"
#include"Bullet.h"
#include"cocos2d.h"
USING_NS_CC;

//�����ӵ�
Bullet::Bullet(const std::string pngName, int _attack, int _costenergy, int _knock, int _accurate) {
	Props(pngName);
	//���ñ��
	_sprite->setTag(20);

	(this->attack) = _attack;
	(this->costenergy) = _costenergy;
	(this->knock) = _knock;
	(this->accurate) = _accurate;
}

Bullet::Bullet(const std::string pngName) {
	Props(pngName);
	//���ñ��
	_sprite->setTag(20);
}

//�޸�����
void Bullet::setattack(int _attack) {
    (this->attack) = _attack;
}

void Bullet::setcostenergy(int _costenergy) {
	(this->costenergy) = _energy;
}

void Bullet::setknock(int _knock) {
	(this->knock) = _knock;
}

void Bullet::setattack(int _attack) {
	(this->accurate) = _accurate;
}

//�����ӵ�
bool Bullet::onTouchBegan(Touch* touch, Event* unused_event) {
	// ���������ڵ�λ�ô���һ���ӵ���
	auto bullet = Bullet(pngName);

	//��ȡ����������꣬����������������_player��ƫ������
	Vec2 touchLocation = touch->getLocation();
	Vec2 offset = touchLocation - _player->getPosition();
	// ��ƫ����ת��Ϊ��λ������������Ϊ1��������
	offset.normalize();
	// �������1000�����һ��ָ���û���������ĳ���Ϊ1000��������
	auto shootAmount = offset * 1000;
	// ����������ӵ����ڵ�λ����ȥ�������������һ��Ŀ��λ�á�
	auto realDest = shootAmount + bullet->getPosition();
	// ��������2�����ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ���
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	bullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

	return true;
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