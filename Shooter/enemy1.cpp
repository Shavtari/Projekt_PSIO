#include "enemy1.h"

void enemy1::initialVariables()
{
    this->type = 1;
    this->hpMax = 10;
    this->hp = hpMax;
    this->attackCdMax = 500.f;
    this->attackCd = rand()%int(this->attackCdMax);
    this->projectileSpeed = 0.25;
    this->projectileNumber = 3;
    this->points = 100;
}

void enemy1::initialTexture()
{
    if(!this->texture.loadFromFile("textures/enemy1.png")){
        std::cout << "Couldn't load enemy1.png" << "\n";
    }
}

void enemy1::initialSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.27, 0.27);
}

enemy1::enemy1()
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
}

enemy1::enemy1(int positionX, int positionY)
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
    this->sprite.setPosition(positionX, positionY);
}

enemy1::~enemy1()
{

}
