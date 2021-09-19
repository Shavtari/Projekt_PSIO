#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H
#include <enemy.h>

class enemyBoss : public Enemy
{
private:
    void initialVariables();
    void initialTexture();
    void initialSprite();
public:
    enemyBoss();
    enemyBoss(int positionX, int positionY);
    virtual ~enemyBoss();
};

#endif // ENEMYBOSS_H
