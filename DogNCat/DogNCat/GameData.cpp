#include "GameData.h"

GameData::GameData(int x, int y, int width, int height, std::string name, int value, std::string image) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->name = name;
	this->value = value;
	this->image = image;
}

int GameData::getX() {
	return this->x;
}

int GameData::getY() {
	return this->y;
}

void GameData::setX(int x) {
	this->x = x;
}
void GameData::setY(int y) {
	this->y = y;
}
int GameData::getW() {
	return this->width;
}
int GameData::getH() {
	return this->height;
}
std::string GameData::getName() {
	return this->name;
}
int GameData::getValue() {
	return this->value;
}
void GameData::setImg(std::string img) {
	this->image = img;
}

GameData::~GameData(){}
