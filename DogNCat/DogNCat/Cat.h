#ifndef CAT_H

#define CAT_H
#include "Dog.h"
#include "Tree.h"
#include "Fance.h"
#include "MovingObject.h"
class Cat :
    public MovingObject
{
public:
    Cat(MovingObject::Direction direction, int x, int y, Dog* dog);
    ~Cat();
    int getCooldown();
    void reduceCooldown();
    void resetCooldown();
    void getOnTree(Tree* tree);
    void getOnFance(Fance* fance);
    void getOffTree();
    void getOffFance();
    Tree* getTree();
    Fance* getFance();
    bool getCatched();
    void setCatched();
    bool getCatchable();
    void reverseDirection(MovingObject::Direction direction);
    void changeDirection();
    void setRandomDirection();
    void collisionReact();
    void setImage();
    void Move(MovingObject::Direction direction);
    void reduceTimeToHide();
    int getTimeLeftToHide();

private:
    Dog* dog;
    int cooldown;
    int timeLeftToHide;
    Tree* tree;
    Fance* fance;
    int rotateInterval;
    bool catchable;
    bool catched;
};

#endif // !CAT_H



