#ifndef PHYSICAL_H
#define PHYSICAL_H
#include <string>
class Physical
{

public:
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual void setX(int) = 0;
	virtual void setY(int) = 0;
	virtual int getW() = 0;
	virtual int getH() = 0;
	virtual void collisionReact() = 0;
	virtual ~Physical() = default;

};

#endif // !PHYSICAL_H



