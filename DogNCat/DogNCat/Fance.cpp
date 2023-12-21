#include "Fance.h"
Fance::Fance(int x, int y): GameObject(x, y) {
	this->height = 50;
	this->width = 100;
	this->busy = false;
	this->image = "fance.png";
}
void Fance::setBusy() {
	this->busy = true;
}

void Fance::unsetBusy() {
	this->busy = false;
}

bool Fance::getBusy() {
	return busy;
}

std::string Fance::getImage() {
	return image;
}