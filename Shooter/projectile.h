#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Projectile
{
private:
    sf::Sprite shape;
    sf::Texture* texture;
    sf::Vector2f direction;
    float movementSpeed;
    char type;
public:
    Projectile();
    Projectile(sf::Texture* texture,float scale, float positionX, float positionY, float direcitonX, float directionY, float movementSpeed);
    Projectile(sf::Texture* texture,float scale, float positionX, float positionY, float direcitonX, float directionY, float movementSpeed, char type);
    virtual ~Projectile();

    const sf::FloatRect getBounds() const;
    const char getType() const;

    void update();
    void render(sf::RenderTarget* target);
};

#endif // PROJECTILE_H
