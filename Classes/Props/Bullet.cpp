#include"Props.h"
#include"Bullet.h"
#include"cocos2d.h"
USING_NS_CC;

//创建子弹
Bullet::Bullet(const std::string pngName, int _attack, int _costenergy, int _knock, int _accurate) {
	Props(pngName);
	//设置标记
	_sprite->setTag(20);

	(this->attack) = _attack;
	(this->costenergy) = _costenergy;
	(this->knock) = _knock;
	(this->accurate) = _accurate;
}

Bullet::Bullet(const std::string pngName) {
	Props(pngName);
	//设置标记
	_sprite->setTag(20);
}

//修改属性
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

//发射子弹
bool Bullet::onTouchBegan(Touch* touch, Event* unused_event) {
	// 在武器所在的位置创建一个子弹。
	auto bullet = Bullet(pngName);

	//获取触摸点的坐标，并计算这个点相对于_player的偏移量。
	Vec2 touchLocation = touch->getLocation();
	Vec2 offset = touchLocation - _player->getPosition();
	// 将偏移量转化为单位向量，即长度为1的向量。
	offset.normalize();
	// 将其乘以1000，获得一个指向用户触屏方向的长度为1000的向量。
	auto shootAmount = offset * 1000;
	// 将此向量添加到飞镖的位置上去，这样你就有了一个目标位置。
	auto realDest = shootAmount + bullet->getPosition();
	// 将飞镖在2秒内移动到目标位置，然后将它从场景中移除。
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	bullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

	return true;
}
//子弹射中怪
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