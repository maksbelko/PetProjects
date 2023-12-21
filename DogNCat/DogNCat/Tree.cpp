#include "Tree.h"
Tree::Tree(int x, int y): GameObject(x, y) {
	this->width = 50;
	this->height = 100;
	this->image = std::string("tree.png");
	this->busy = false;
}
void Tree::setBusy() {
	this->busy = true;
}

void Tree::unsetBusy() {
    this->busy = false;
}

std::string Tree::getImage() {
	return image;
}

