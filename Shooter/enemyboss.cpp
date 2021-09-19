#include "enemyboss.h"

void enemyBoss::initialVariables()
{
    this->type = 2;
    this->hpMax = 2000;
    this->hp = hpMax;
    this->attackCdMax = 50.f;
    this->attackCd = 0.f;
    this->projectileSpeed = 0.25;
    this->projectileNumber = 10;
    this->points = 1000;
    this->phaseTimer = 0;
    this->phaseTimerMax = 500;
    this->currentPhase = 0;
}

void enemyBoss::initialTexture()
{
    if(!this->texture.loadFromFile("textures/boss.png")){
        std::cout << "Couldn't load boss.png" << "\n";
    }
}

void enemyBoss::initialSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.2, 1.2);
}

enemyBoss::enemyBoss()
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
}

enemyBoss::enemyBoss(int positionX, int positionY)
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
    this->sprite.setPosition(positionX, positionY);
}

enemyBoss::~enemyBoss()
{

}

