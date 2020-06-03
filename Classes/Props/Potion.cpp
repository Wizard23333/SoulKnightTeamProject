#include"cocos2d.h"
#include"Props.h"
#include"Potion.h"

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
bool Potion::onContactpresolve(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag()>=100||nodeB->getTag()>=100)
	{
		if (nodeA->getTag() == tag_of_the_hero)//Ӣ�۵ı��
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == tag_of_the_hero)//Ӣ�۵ı��
		{
			nodeA->removeFromParentAndCleanup(true);
		}
	}
	return true;
}

//ҩˮʹ��
bool Potion::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T)
	{
		auto temptag = 100 + this->_sprite->getTag();
		this->_sprite->setTag(temptag);
	}
	return true;
}

bool Potion::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode)
{
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T)
	{
		auto temptag = -100 + this->_sprite->getTag();
		this->_sprite->setTag(temptag);
	}
	return true;
}