#include"Props.h"

USING_NS_CC;

//��Ӣ�۴�����ҩˮ
Potion::Potion(const std::string pngName) {
	Props(pngName);
	//���ñ��
	_sprite->setTag(10);
}

//�ڱ��䴦����ҩˮ
Potion::Potion(const std::string pngName, Node* Box) {
	Props(pngName,Box);
	//���ñ��
	_sprite->setTag(10);
}

//�������Ժ���
void Potion::setblood(int _blood) {
	(this->blood) = _blood;
}
void Potion::setenergy(int _energy) {
	(this->energy) = _energy;
}

//ҩˮ��ײ����
bool Potion::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == tag_of_the_hero)//Ӣ�۵ı��
	{
		nodeB->removeFromParentAndCleanup(true);
	}
	else if (nodeB->getTag() == tag_of_the_hero)//Ӣ�۵ı��
	{
		nodeA->removeFromParentAndCleanup(true);
	}

	return true;
}