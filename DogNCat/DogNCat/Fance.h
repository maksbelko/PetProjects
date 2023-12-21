#ifndef FANCE_H
#define FANCE_H

#include "GameObject.h"

class Fance :
    public GameObject

{
public:
    Fance(int, int);
    void setBusy();
    void unsetBusy();
    bool getBusy();
    std::string getImage();
protected:
    bool busy;
};

#endif // !FANCE_H


