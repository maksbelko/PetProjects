#include "MovingObject.h"

MovingObject::MovingObject(int x, int y, MovingObject::Direction direction) : GameObject(x, y) {
	this->direction = direction;
}

MovingObject::Direction MovingObject::getDirection() {
	return direction;
}

int MovingObject::getSpeed() {
	return speed;
}

void MovingObject::setSpeed(int speed) {
	this->speed = speed;
}

bool MovingObject::objectOutOfFrame() {

	if ((direction == Up && y <= 0) || (direction == Down && y >= 800 - height) ||
		(direction == Left && x <= 0) || (direction == Right && x >= 800 - width)) {
		this->canMove = false;
		return true;
	}
	else {
		return false;
	}
}

void MovingObject::Rotation(MovingObject::Direction direction) {
	if (this->direction != direction) {
		this->canMove = true;
		this->direction = direction;
	}
}

void MovingObject::Move(MovingObject::Direction direction) {
	if (!objectOutOfFrame() && canMove == true) {
		switch (direction)
		{
		case Up:
			y -= speed;
			break;
		case Down:
			y += speed;
			break;
		case Left:
			x -= speed;
			break;
		case Right:
			x += speed;
			break;
		}
	}
	else {
		canMove = false;
	}
}

std::string MovingObject::getImage()
{
	return image;
}

void MovingObject::collisionReact()
{
	canMove = false;
	switch (direction) {
	case Up:
		this->y += 7;
		break;
	case Down:
		this->y -= 7;
		break;
	case Left:
		this->x += 7;
		break;
	case Right:
		this->x -= 7;
		break;
	}
}
