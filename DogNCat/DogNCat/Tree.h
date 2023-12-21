#ifndef TREE_H
#define TREE_H

#include "GameObject.h"

class Tree :
    public GameObject
{
public:
    Tree(int x , int y);
    void setBusy();
    void unsetBusy();
    std::string getImage();
protected:
    bool busy;

};
#endif // !TREE_H


