#include "Dog.h"
#include <iostream>
Dog::Dog(MovingObject::Direction direction, int x, int y) : MovingObject(x, y, direction)
{
	this->width = 30;
	this->height = 30;
	this->canMove = true;
	this->lifes = 3;
	this->speed = 4;
	this->image = "dog_left.png";
	this->cooldown = 0;
}

Dog::~Dog(){}

void Dog::setImage()
{
	switch (direction)
	{
	case MovingObject::Up:
		break;
	case MovingObject::Down:
		break;
	case MovingObject::Left:
		this->image = "dog_left.png";
		break;
	case MovingObject::Right:
		this->image = "dog_right.png";
		break;
	default:
		break;
	}
}

std::string Dog::getImage()
{
	return image;
}

void Dog::setImageToDog(std::string path)
{
	this->image = path;
}

void Dog::Move(MovingObject::Direction direction)
{
	Rotation(direction);
	this->setImage();
	this->MovingObject::Move(direction);
}

void Dog::shocked() {
	setCooldown();
	canMove = false;
}

void Dog::setCooldown() {
	cooldown = 3;
}

void Dog::unshocked() {
	canMove = true;
}

bool Dog::getCanMove()
{
	return canMove;
}

void Dog::reduceCooldown() {
	cooldown -= 1;
}

int Dog::getCooldown() {
	return cooldown;
}

void Dog::decreaseLifes()
{
	lifes--;
}

void Dog::increaseLifes()
{
	lifes++;
}


int Dog::getLifes()
{
	return lifes;
}

