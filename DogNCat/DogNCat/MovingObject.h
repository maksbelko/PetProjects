#pragma once
#include "GameObject.h"
class MovingObject :
    public GameObject
{
public:
    enum Direction { Up, Down, Left, Right };
    MovingObject(int, int, Direction);
    virtual ~MovingObject() = default;
    virtual void Move(Direction);
    std::string getImage();
    void collisionReact();
    void Rotation(Direction direction);
    Direction getDirection();
    int getSpeed();
    bool objectOutOfFrame();
    void setSpeed(int);
protected:
    Direction direction;
    bool canMove;
    int speed;
    
};

