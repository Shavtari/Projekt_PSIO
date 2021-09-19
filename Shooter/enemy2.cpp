#include "enemy2.h"

void enemy2::initialVariables()
{
    this->type = 1;
    this->hpMax = 5;
    this->hp = hpMax;
    this->attackCdMax = 200.f;
    this->attackCd = rand()%int(this->attackCdMax);
    this->projectileSpeed = 1;
    this->projectileNumber = 2;
    this->points = 75;
}

void enemy2::initialTexture()
{
    if(!this->texture.loadFromFile("textures/enemy2.png")){
        std::cout << "Couldn't load enemy2.png" << "\n";
    }
}

void enemy2::initialSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.2, 0.2);
}

enemy2::enemy2()
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
}

enemy2::enemy2(int positionX, int positionY)
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
    this->sprite.setPosition(positionX, positionY);
}

enemy2::~enemy2()
{

}
