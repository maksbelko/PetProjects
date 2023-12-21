#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Physical.h"
class GameObject :
	public Physical
{
public:
	GameObject(int x, int y);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	int getW();
	int getH();
	void collisionReact();
	virtual void setImage();
	std::string getImage();
	~GameObject();

protected:
	int x;	// left cord
	int y;	// top cord
	int width;
	int height;
	std::string image;

};
#endif // !GAME_OBJECT_H
