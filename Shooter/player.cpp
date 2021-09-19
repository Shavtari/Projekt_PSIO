#include "player.h"

void Player::initialVariables()
{
    this->movementSpeed = 2.f;
    this->attackCdMax = 10.f;
    this->attackCd = this->attackCdMax;
    this->abilityCdMax = 1000.f;
    this->abilityCd = abilityCdMax/2.f;
    this->projectileNumber = 1;
    this->damage = 2;
    this->lives = 4;
}

void Player::initialTexture()
{
    if(!this->texture.loadFromFile("textures/ship1.png")){
        std::cout << "Couldn't load ship1.png" << "\n";
    }
}

void Player::initialSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.12, 0.12);
}

Player::Player()
{
    this->initialVariables();
    this->initialTexture();
    this->initialSprite();
}

Player::~Player()
{

}

const sf::Vector2f &Player::getPosition() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int Player::getProjectileNumber() const
{
    return this->projectileNumber;
}

const int Player::getLives() const
{
    return this->lives;
}

const int Player::getDamage() const
{
    return this->damage;
}

const int Player::getAbilityCd() const
{
    return this->abilityCd;
}

const int Player::getAbilityCdMax() const
{
    return this->abilityCdMax;
}

void Player::setPosition(const sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Player::move(const float direcionX, const float directionY)
{
    this->sprite.move(this->movementSpeed*direcionX, this->movementSpeed*directionY);
}

void Player::losingLife()
{
    this->lives--;
}

void Player::gettingLife()
{
    this->lives++;
}

void Player::gettingDamage()
{
    this->damage++;
}

void Player::gettingProjectiles()
{
    this->projectileNumber++;
}

const bool Player::attackAvailable()
{
    if(this->attackCd >= this->attackCdMax){
        this->attackCd=0.f;
        return true;
    }
    return false;
}

const bool Player::abilityAvailable()
{
    if(this->abilityCd > 0){
        this->abilityCd-=2.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if(this->attackCd < this->attackCdMax){
        this->attackCd += 0.5f;
    }
}

void Player::updateAbility()
{
    if(this->abilityCd+250 < this->abilityCdMax){
        this->abilityCd += 250.f;
    }
    else{
        this->abilityCd = this->abilityCdMax;
    }
}

//Functions
void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
