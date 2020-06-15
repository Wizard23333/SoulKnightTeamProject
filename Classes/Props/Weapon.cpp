#include"cocos2d.h"
#include"Props.h"
#include"Bullet.h"
#include"Weapon.h"
USING_NS_CC;

//��������
Weapon::Weapon(const std::string pngName) :Props(pngName)
{
	_sprite->setTag(5);
	_sprite->setAnchorPoint(Vec2(0,0));
	tagofbullet = _sprite->getTag()+5;
};

bool Weapon::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	this->_sprite->setOpacity(255);
	return true;
};


bool Weapon::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
	if (this->tagofbullet >= 12)//Զ����������
	{
		//��ȡ����������꣬����������������_player��ƫ������
		Vec2 touchLocation = touch->getLocation();
		Vec2 offset = touchLocation - this->_sprite->getPosition();
		// ��ƫ����ת��Ϊ��λ������������Ϊ1��������
		offset.normalize();
		// �������1000�����һ��ָ���û���������ĳ���Ϊ1000��������
		auto shootAmount = offset * 1000;
		// ����������ӵ����ڵ�λ����ȥ�������������һ��Ŀ��λ�á�
		auto realDest = shootAmount + this->_sprite->getPosition();
		// ��������1�����ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ���
		auto actionMove = MoveTo::create(1.0f, realDest);
		auto actionRemove = RemoveSelf::create();

		int temptag = this->tagofbullet;
		Bullet bullet1 = Bullet(parameter[temptag].getpngname());
		bullet1._sprite->setPosition(this->_sprite->getPosition());
		bullet1._sprite->setScale(0.10);
        //add
        bullet1._sprite->setTag(temptag);
        auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
        physicbody->setDynamic(false);
        physicbody->setCategoryBitmask(32);
        physicbody->setContactTestBitmask(16);
        bullet1._sprite->setPhysicsBody(physicbody);
        
		(this->_sprite->getParent())->addChild(bullet1._sprite);
		bullet1._sprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));
	}
	else if(this->tagofbullet == 11)//����ǰ��
	{
		auto realDest = Vec2(40,0) + this->_sprite->getPosition();
		auto actionMove = MoveTo::create(0.1f, realDest);
		auto actionRemove = RemoveSelf::create();
		this->_sprite ->setOpacity(0);
		int temptag = this->tagofbullet;
		Bullet bullet1 = Bullet(parameter[temptag].getpngname());
		bullet1._sprite->setScale(0.10);
        //add
        bullet1._sprite->setTag(temptag);
        auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
        physicbody->setDynamic(false);
        physicbody->setCategoryBitmask(32);
        physicbody->setContactTestBitmask(16);
        bullet1._sprite->setPhysicsBody(physicbody);
        
		bullet1._sprite->setPosition(this->_sprite->getPosition());
		(this->_sprite->getParent())->addChild(bullet1._sprite);
		bullet1._sprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));
	}
	else if (this->tagofbullet == 10)//��������
	{
		auto rotateBy = RotateBy::create(0.4f, 720.0f);
		auto actionRemove = RemoveSelf::create();
		this->_sprite->setOpacity(0);
		int temptag = this->tagofbullet;
		Bullet bullet1 = Bullet(parameter[temptag].getpngname());
		bullet1._sprite->setScale(0.10);
        //add
        bullet1._sprite->setTag(temptag);
        auto physicbody = cocos2d::PhysicsBody::createBox(this->_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
        physicbody->setDynamic(false);
        physicbody->setCategoryBitmask(32);
        physicbody->setContactTestBitmask(16);
        bullet1._sprite->setPhysicsBody(physicbody);
        
		bullet1._sprite->setPosition(this->_sprite->getPosition());
		(this->_sprite->getParent())->addChild(bullet1._sprite);
		bullet1._sprite->runAction(Sequence::create(rotateBy, actionRemove, nullptr));
	}

	return true;
};

