#ifndef GAME_DATA_H

#define GAME_DATA_H

#include <string>

class GameData {
private:
	int x;	// left cord
	int y;	// top cord
	int width;
	int height;
	std::string image;
	std::string name;
	int value;
	

public:
	GameData(int x, int y, int width, int height, std::string name, int value, std::string image);

	int getX();
	int getY();
	void setX(int);
	void setY(int);
	int getW();
	int getH();
	std::string getName();
	void setImg(std::string);
	int getValue();
	~GameData();
};

#endif // !GAME_DATA_H


