
#ifndef Box_h
#define Box_h
#include "Props.h"
#include "Potion.h"
#include "Weapon.h"
USING_NS_CC;
class Box:public Props
{
public:
    Box(int propsValue = 1, int kind = 1);
    bool onContactBegin(PhysicsContact & contact);
    void openBox();
    Potion _potion;
    Weapon _weapon;
    bool isOpen;
private:
    int kindOfBox;
    int value;
};

#endif /* Box_h */
