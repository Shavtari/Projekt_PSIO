#include "enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

const sf::Vector2f &Enemy::getPosition() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int Enemy::getType() const
{
    return this->type;
}

const int Enemy::getLife() const
{
    return this->hp;
}

const int Enemy::getPoints() const
{
    return this->points;
}

const int Enemy::getProjectileNumber() const
{
    return this->projectileNumber;
}

const int Enemy::getCurrentPhase() const
{
    return this->currentPhase;
}

const float Enemy::getProjectileSpeed() const
{
    return this->projectileSpeed;
}

void Enemy::changePhase(int phase)
{
    switch(phase){
    case 0:
        this->projectileNumber = 6.f;
        this->projectileSpeed = 2.f;
        this->attackCdMax = 25.f;
        this->currentPhase++;
        break;
    case 1:
        this->projectileNumber = 5.f;
        this->projectileSpeed = 3.f;
        this->attackCdMax = 50.f;
        this->currentPhase++;
        break;
    case 2:
        this->projectileNumber = 8.f;
        this->projectileSpeed = 1.5f;
        this->attackCdMax = 50.f;
        this->currentPhase++;
        break;
    case 3:
        this->projectileNumber = 15.f;
        this->projectileSpeed = 0.75f;
        this->attackCdMax = 75.f;
        this->currentPhase = 0;
        break;
    }
}

//Functions
void Enemy::setPosition(const sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

void Enemy::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Enemy::losingLife(int incomingDamage)
{
    this->hp = this->hp - incomingDamage;
}

const bool Enemy::attackAvailable()
{
    if(this->attackCd >= this->attackCdMax){
        this->attackCd=rand()%int(attackCdMax/2.0);
        return true;
    }
    return false;
}

const bool Enemy::phaseAvailable()
{
    if(this->phaseTimer >= this->phaseTimerMax){
        this->phaseTimer=0.f;
        return true;
    }
    return false;
}

void Enemy::updatePhaseTimer()
{
    if(this->phaseTimer < this->phaseTimerMax){
        this->phaseTimer += 0.5f;
    }
}

void Enemy::updateAttack()
{
    if(this->attackCd < this->attackCdMax){
        this->attackCd += 0.5f;
    }
}

void Enemy::update()
{
    this->updateAttack();
    if(this->getType()==2){
        this->updatePhaseTimer();
    }
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
