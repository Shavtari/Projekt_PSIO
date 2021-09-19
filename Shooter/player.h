#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float attackCd;
    float attackCdMax;
    float abilityCd;
    float abilityCdMax;
    int projectileNumber;
    int damage;
    int lives;

    void initialVariables();
    void initialTexture();
    void initialSprite();
public:
    Player();
    virtual ~Player();

    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getBounds() const;
    const int getProjectileNumber() const;
    const int getLives() const;
    const int getDamage() const;
    const int getAbilityCd() const;
    const int getAbilityCdMax() const;

    //Functions
    void setPosition(const sf::Vector2f position);
    void setPosition(const float x, const float y);
    void move(const float direcionX, const float directionY);
    void losingLife();
    void gettingLife();
    void gettingDamage();
    void gettingProjectiles();
    const bool attackAvailable();
    const bool abilityAvailable();
    void updateAttack();
    void updateAbility();
    void update();
    void render(sf::RenderTarget& target);
};

#endif // PLAYER_H
