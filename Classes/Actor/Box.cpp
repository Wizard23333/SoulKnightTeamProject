
#include "Box.h"
Box::Box(int propsValue, int kind)
:Props("Box.png")
{
    
    this->_sprite->setTag(1000);
    this->isOpen = false;
    this->kindOfBox = kind;//1是药水箱子 2是武器箱子
    if(kind == 1)
    {
        value = propsValue;
    }
    else if(kind == 2)
    {
        value = propsValue;
    }
}

bool Box::onContactBegin(PhysicsContact & contact)
{
    if(isOpen == true)
        return false;
    
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if(nodeA && nodeB)
    {
        auto posA = nodeA->getPosition();
        auto posB = nodeB->getPosition();
        log("\n%d", nodeA->getTag());
        log("%d", nodeB->getTag());
        if(posA == this->_sprite->getPosition() || posB == this->_sprite->getPosition())
        {
            if(nodeA->getTag() == 999 && nodeB->getTag() == 1000)
            {
                this->openBox();
            }
            if(nodeB->getTag() == 999 && nodeA->getTag() == 1000)
            {
                this->openBox();
            }
        }
    }
    return true;
}


void Box::openBox()//打开箱子的操作
{
    isOpen = true;
    auto fadeOut = FadeOut::create(1.0f);
    auto removeSelf = RemoveSelf::create();
    auto position = _sprite->getPosition();
    auto parent = this->_sprite->getParent();
    if(kindOfBox)//添加药水
    {
        log("position.x=%f position.y=%f", position.x, position.y);
        float x = position.x;
        float y = position.y;
        _potion = Potion(parameter[value - 1].getpngname());
		_potion._sprite->setPosition(position);
        log("pppposition.x=%f pppposition.y=%f", _potion._sprite->getPosition().x, _potion._sprite->getPosition().y);
        log("%s",parameter[value].getpngname().c_str());
        _potion._sprite->setScale(0.10);
        _potion._sprite->setTag(value);
        parent->addChild(_potion._sprite, 1);
    }
    else if(kindOfBox == 2)
    {
        log("2");
        _weapon._sprite->setPosition(position);
        //parent->addChild(_weapon._sprite, 1);
    }
    //this->_sprite->runAction(Sequence::create(fadeOut, removeSelf, nullptr));

}


