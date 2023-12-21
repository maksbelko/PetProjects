#ifndef DOG_H

#define DOG_H

#include "MovingObject.h"
#include <SFML/Graphics.hpp>

class Dog :
	public MovingObject {
public:
	Dog(MovingObject::Direction direction, int x, int y);
	~Dog();
	void setImage();
	std::string getImage();
	void setImageToDog(std::string path);
	void Move(MovingObject::Direction direction);
	void shocked();
	void unshocked();
	bool getCanMove();
	void setCooldown();
	void reduceCooldown();
	int getCooldown();
	void decreaseLifes();
	void increaseLifes();
	int getLifes();

private:
	int lifes;
	int cooldown;

};



#endif // !DOG_H
