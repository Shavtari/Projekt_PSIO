#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    int type;
    int hpMax;
    int hp;
    float attackCd;
    float attackCdMax;
    float projectileSpeed;
    float phaseTimer = 0;
    float phaseTimerMax = 1;
    int currentPhase;
    int projectileNumber;
    int points;
public:
    Enemy();
    virtual ~Enemy();

    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getBounds() const;
    const int getType() const;
    const int getLife() const;
    const int getPoints() const;
    const int getProjectileNumber() const;
    const int getCurrentPhase() const;
    const float getProjectileSpeed() const;

    //Functions
    void changePhase(int phase);
    void setPosition(const sf::Vector2f position);
    void setPosition(const float x, const float y);
    void losingLife(int incomingDamage);
    const bool attackAvailable();
    const bool phaseAvailable();
    void updatePhaseTimer();
    void updateAttack();
    void update();
    void render(sf::RenderTarget* target);


};

#endif // ENEMY_H
