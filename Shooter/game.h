#ifndef GAME_H
#define GAME_H
#include <player.h>
#include <projectile.h>
#include <enemy.h>
#include <enemy1.h>
#include <enemy2.h>
#include <enemyboss.h>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

class Game
{
private:

    //Window
    sf::RenderWindow* window;
    //sf::Event event;

    //Textures
    std::map<std::string, sf::Texture*> textures;

    //Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    //UI
    sf::Font font;
    sf::Text pointsText;
    sf::Text scoreMultiText;
    sf::Text livesText;
    sf::Text gameOverText;
    sf::Text victoryText;
    sf::RectangleShape abilityBar;
    sf::RectangleShape abilityBarBack;

    //Projectiles
    std::vector<Projectile*> projectiles;
    std::vector<Projectile*> enemyProjectiles;
    std::vector<Projectile*> powerUps;

    //Player
    Player* player;

    //Game logic
    int points;
    float scoreMulti;
    float scoreMultiCounter;

    //Enemies
    int levelNumber;
    std::fstream level;
    std::vector<Enemy*> enemies;

    //Private functions
    void initialVariables();
    void initialWindow();
    void initialTextures();
    void initialBackground();
    void initialPlayer();
    void initialEnemies();
    void initialUI();

public:
    Game();
    virtual ~Game();

    const bool isRunning() const;

    //Functions
    void scoreMultiIncrease();
    void updateEvents();
    void updateLevel();
    void updatePlayerInput();
    void updateProjectiles();
    void updateEnemies();
    void updateCollision();
    void updateUI();
    void update();
    void render();

};

#endif // GAME_H
