#include "GameObject.h"

GameObject::GameObject(int x, int y) {
	this->x = x;
	this->y = y;
}

int GameObject::getX() {
	return this->x;
}

int GameObject::getY() {
	return this->y;
}

void GameObject::setX(int x) {
	this->x = x;
}
void GameObject::setY(int y) {
	this->y = y;
}
int GameObject::getW() {
	return this->width;
}
int GameObject::getH() {
	return this->height;
}

void GameObject::collisionReact() {}

void GameObject::setImage()
{
}

std::string GameObject::getImage()
{
	return image;
}

GameObject::~GameObject() {}
