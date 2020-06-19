#include"cocos2d.h"
#include"Props.h"
#include"Potion.h"

USING_NS_CC;

//��Ӣ�۴�����ҩˮ
Potion::Potion(const std::string pngName):Props(pngName) {
	//���ñ��
	_sprite->setTag(10);
    isItUsed = false;
}

/*Potion* Potion::PotionCreate(const std::string pngName)
{
	_sprite->setTag(10);
	propsCreate(pngName);
	return this;
}*/

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
    if(isItUsed == true)
        return false;
    
    if(nodeA && nodeB)
    {
        log("%d",nodeA->getTag());
        log("%d",nodeB->getTag());
        auto posA = nodeA->getPosition();
        auto posB = nodeB->getPosition();
        if(posA == this->_sprite->getPosition() || posB == this->_sprite->getPosition())
        {
            if ((nodeA->getTag()>=100 && nodeA ->getTag() <= 110)||(nodeB->getTag()>=100 && nodeB->getTag() <= 110))
            {
                if (nodeA->getTag() == 999)
                {
                    isItUsed = true;
                    nodeB->removeFromParentAndCleanup(true);
                }
                else if (nodeB->getTag() == 999)
                {
                    isItUsed = true;
                    nodeA->removeFromParentAndCleanup(true);
                }
            }
        }
    }
    
    return true;
}
//ҩˮʹ��
bool Potion::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode)
{
    log("%d", isItUsed);
    if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T && isItUsed == false)
    {
        //auto temptag = 100 + this->_sprite->getTag();
        auto temptag = this->_sprite->getTag() < 100 ? this->_sprite->getTag() + 100 : this->_sprite->getTag();
        this->_sprite->setTag(temptag);
    }
    return true;
}

bool Potion::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode)
{
    if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T && isItUsed == false)
    {
        //auto temptag = -100 + this->_sprite->getTag();
        auto temptag = this->_sprite->getTag() > 100 ? this->_sprite->getTag() - 100 : this->_sprite->getTag();
        this->_sprite->setTag(temptag);
    }
    return true;
}
