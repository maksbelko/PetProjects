#include "Cat.h"
#include <iostream>
#include <ctime>


Cat::Cat(Direction direction, int x, int y, Dog* dog): MovingObject(x, y, direction) {
	this->width = 30;
	this->height = 30;
	this->speed = 2;
	this->canMove = true;
	this->catchable = true;
	this->catched = false;
	this->cooldown = 0;
	this->rotateInterval = 0;
	this->timeLeftToHide = 0;
	this->dog = dog;
	this->tree = nullptr;
	this->fance = nullptr;
	this->image = "cat_left.png";
}

Cat::~Cat(){}


int Cat::getCooldown() {
	return cooldown;
}

void Cat::reduceCooldown() {
	cooldown -= 1;
}

void Cat::resetCooldown() {
	cooldown = 10;
}

void Cat::getOnTree(Tree* tree) {
	this->catchable = false;
	this->canMove = false;
	this->tree = tree;
	this->tree->setBusy();
	this->x = tree->getX() + (tree->getW() - width) / 2;
	this->y = tree->getY() + height;
	this->timeLeftToHide = 3;
}

void Cat::getOnFance(Fance* fance) {
	this->catchable = false;
	this->canMove = false;
	this->fance = fance;
	this->fance->setBusy();
	this->x = fance->getX() + (fance->getW() - width) / 2;
	this->y = fance->getY() + height;
	this->timeLeftToHide = 3;
}

void Cat::getOffTree() {
	this->catchable = true;
	this->canMove = true;
	this->tree->unsetBusy();
	this->x = tree->getX() + tree->getW();
	this->y = tree->getY() + tree->getH();
	this->tree = nullptr;
	this->resetCooldown();
}

void Cat::getOffFance() {
	this->catchable = true;
	this->canMove = true;
	this->fance->unsetBusy();
	this->x = fance->getX() + fance->getW();
	this->y = fance->getY() + fance->getH();
	this->fance = nullptr;
	this->resetCooldown();
}

Tree* Cat::getTree() {
	return tree;
}



Fance* Cat::getFance() {
	return fance;
}

bool Cat::getCatched() {
	return catched;
}

void Cat::setCatched() {
	this->catched = true;
}

bool Cat::getCatchable() {
	return catchable;
}

void Cat::reverseDirection(MovingObject::Direction direction) {
	switch (direction)
	{
	case Up:
		Rotation(Down);
		break;
	case Down:
		Rotation(Up);
		break;
	case Left:
		Rotation(Right);
		break;
	case Right:
		Rotation(Left);
		break;
	}
}

void Cat::changeDirection() {
	switch (direction)
	{
	case Up:
		Rotation(Left);
		break;
	case Down:
		Rotation(Right);
		break;
	case Left:
		Rotation(Up);
		break;
	case Right:
		Rotation(Down);
		break;
	}

}

void Cat::setRandomDirection() {
	srand(time(0));
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		Rotation(Right);
		break;
	case 1:
		Rotation(Left);
		break;
	case 2:
		Rotation(Up);
		break;
	case 3:
		Rotation(Down);
		break;
	}
}

void Cat::collisionReact() {
	MovingObject::collisionReact();
	changeDirection();
}

void Cat::setImage() {
	switch (direction)
	{
	case Left:
		this->image = "cat_left.png";
		break;
	case Right:
		this->image = "cat_right.png";
	case Up:
	case Down:
	default:
		break;
	}
}

void Cat::Move(MovingObject::Direction direction)
{
	rotateInterval += 50;

	if (rotateInterval % 1000 == 0) {
		setRandomDirection();
	}

	if (objectOutOfFrame() == true) {
		reverseDirection(this->direction);
	}
	else {
		MovingObject::Move(direction);
	}

	setImage();

}

void Cat::reduceTimeToHide()
{
	timeLeftToHide--;
}

int Cat::getTimeLeftToHide()
{
	return timeLeftToHide;
}
