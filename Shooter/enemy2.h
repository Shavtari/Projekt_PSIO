#ifndef ENEMY2_H
#define ENEMY2_H
#include <enemy.h>

class enemy2 : public Enemy
{
private:
    void initialVariables();
    void initialTexture();
    void initialSprite();
public:
    enemy2();
    enemy2(int positionX, int positionY);
    virtual ~enemy2();
};

#endif // ENEMY2_H
