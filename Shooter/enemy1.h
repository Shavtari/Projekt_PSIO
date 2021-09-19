#ifndef ENEMY1_H
#define ENEMY1_H
#include <enemy.h>

class enemy1 : public Enemy
{
private:
    void initialVariables();
    void initialTexture();
    void initialSprite();
public:
    enemy1();
    enemy1(int positionX, int positionY);
    virtual ~enemy1();
};

#endif // ENEMY1_H
