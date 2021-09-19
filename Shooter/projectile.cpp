#include "projectile.h"

Projectile::Projectile()
{

}

const sf::FloatRect Projectile::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const char Projectile::getType() const
{
    return this->type;
}

Projectile::Projectile(sf::Texture* texture,float scale, float positionX, float positionY, float directionX, float directionY, float movementSpeed)
{
    this->shape.setTexture(*texture);
    this->shape.scale(scale, scale);
    this->shape.setPosition(positionX-shape.getGlobalBounds().width/2.f, positionY-shape.getGlobalBounds().height);
    this->direction.x= directionX;
    this->direction.y= directionY;
    this->movementSpeed = movementSpeed;
    this->type = 'P';
}

Projectile::Projectile(sf::Texture *texture, float scale, float positionX, float positionY, float directionX, float directionY, float movementSpeed, char type)
{
    this->shape.setTexture(*texture);
    this->shape.scale(scale, scale);
    this->shape.setPosition(positionX-shape.getGlobalBounds().width/2.f, positionY-shape.getGlobalBounds().height);
    this->direction.x= directionX;
    this->direction.y= directionY;
    this->movementSpeed = movementSpeed;
    this->type = type;
}

Projectile::~Projectile()
{

}

void Projectile::update()
{
    this->shape.move(this->movementSpeed * this->direction);
}

void Projectile::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
