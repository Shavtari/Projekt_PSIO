#include "game.h"


//Private functions
void Game::initialVariables()
{
    this->window = nullptr;

    //Game logic
    this->levelNumber=1;
    this->points = 0;
    this->scoreMulti = 1.f;
    this->scoreMultiCounter = 0.f;

}

void Game::initialWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1000,900), "Shooter", sf::Style::Titlebar|sf::Style::Close);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initialTextures()
{
    this->textures["PROJECTILE"] = new sf::Texture();
    this->textures["PROJECTILE"]->loadFromFile("textures/proj1.png");
    this->textures["ENEMYPROJ1"] = new sf::Texture();
    this->textures["ENEMYPROJ1"]->loadFromFile("textures/proj2.png");
    this->textures["HPPACK"] = new sf::Texture();
    this->textures["HPPACK"]->loadFromFile("textures/PUhp.png");
    this->textures["DMGUP"] = new sf::Texture();
    this->textures["DMGUP"]->loadFromFile("textures/PUdmg.png");
    this->textures["PROJUP"] = new sf::Texture();
    this->textures["PROJUP"]->loadFromFile("textures/PUproj.png");
    this->textures["BATTERY"] = new sf::Texture();
    this->textures["BATTERY"]->loadFromFile("textures/PUability.png");
}

void Game::initialBackground()
{
    if (!this->backgroundTexture.loadFromFile("textures/background1.png"))
        {
            std::cout << "Couldn't load background1.png" << "\n";
        }

        this->backgroundSprite.setTexture(this->backgroundTexture);
}

void Game::initialPlayer()
{
    this->player = new Player();
    this->player->setPosition(this->window->getSize().x/2.f, this->window->getSize().y*0.75f);
}

void Game::initialEnemies()
{
    this->level.open("levels/level"+std::to_string(levelNumber)+".txt", std::ios::in);
    std::string line;
    int x=0, y=0;
    while(std::getline(level, line)){
       for (char c : line){
           switch(c){
           case ' ':
               break;
           case '1':
               enemies.emplace_back(new enemy1(x*100+85, y*100+85));
               break;
           case '2':
               enemies.emplace_back(new enemy2(x*100+85, y*100+85));
               break;
           case '3':
               enemies.emplace_back(new enemyBoss(x*100+85, y*100+85));
               break;
           }
           x++;
       }
       x=0;
       y++;
    }
    level.close();
}

void Game::initialUI()
{
    if(!this->font.loadFromFile("font/ArcadeFont.ttf")){
        std::cout<<"Couldn't load font" << "\n";
    }
    this->pointsText.setPosition(15.f, 15.f);
    this->pointsText.setFont(this->font);
    this->pointsText.setCharacterSize(12);
    this->pointsText.setFillColor(sf::Color::White);

    this->scoreMultiText.setPosition(15.f, 30.f);
    this->scoreMultiText.setFont(this->font);
    this->scoreMultiText.setCharacterSize(12);
    this->scoreMultiText.setFillColor(sf::Color::White);

    this->livesText.setPosition(890.f, 15.f);
    this->livesText.setFont(this->font);
    this->livesText.setCharacterSize(12);
    this->livesText.setFillColor(sf::Color::White);

    this->gameOverText.setPosition(175.f, 350.f);
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(75);
    this->gameOverText.setFillColor(sf::Color::White);
    this->gameOverText.setString("GAME OVER");

    this->victoryText.setPosition(250.f, 350.f);
    this->victoryText.setFont(this->font);
    this->victoryText.setCharacterSize(75);
    this->victoryText.setFillColor(sf::Color::White);
    this->victoryText.setString("VICTORY");

    this->abilityBar.setSize(sf::Vector2f(250.f, 25.f));
    this->abilityBar.setFillColor(sf::Color::Yellow);
    this->abilityBar.setPosition(sf::Vector2f(625.f, 10.f));
    this->abilityBarBack = this->abilityBar;
    this->abilityBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

Game::Game()
{
    this->initialVariables();
    this->initialWindow();
    this->initialTextures();
    this->initialBackground();
    this->initialPlayer();
    this->initialEnemies();
    this->initialUI();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
    for(auto &i : this->textures){
        delete i.second;
    }
    for(auto &i : this->projectiles){
        delete i;
    }
    for(auto &i : this->enemies){
        delete i;
    }
    for(auto &i : this->enemyProjectiles){
        delete i;
    }
    for(auto &i : this->powerUps){
        delete i;
    }
}

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

//Functions
void Game::scoreMultiIncrease()
{
    if(this->scoreMultiCounter >= 1000.f){
        scoreMultiCounter=0.f;
        scoreMulti+=0.05f;
    }
    else{
        this->scoreMultiCounter += 1.f;
    }
}

void Game::updateEvents()
{
    sf::Event event;

    while(this->window->pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                this->window->close();
                break;
        }
    }
}

void Game::updateLevel()
{
    if(enemies.size()==0){
        levelNumber++;
        initialEnemies();
    }
}

void Game::updatePlayerInput()
{

    //Movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->player->move(-1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->player->move(1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->player->move(0, -1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->player->move(0, 1);

    //Power
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && this->player->abilityAvailable()){
        this->window->setFramerateLimit(60);
    }
    else{
        this->window->setFramerateLimit(144);
    }

    //Shooting
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->attackAvailable()){
        if(this->player->getProjectileNumber()%2==1){//Odd number of projectiles, middle projectile first
            this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"],
                                        0.2f,//Scale
                                        this->player->getPosition().x + this->player->getBounds().width/2.f, //Spawn position X
                                        this->player->getPosition().y, //Spawn position Y
                                        0.f, //Direction X
                                        -1.f, //Direction Y
                                        4.f)); //Projectile speed
            for(int i=1; i<this->player->getProjectileNumber(); i++){
                if(i%2==0){
                    this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"],
                                                0.2f,//Scale
                                                this->player->getPosition().x + this->player->getBounds().width/2.f, //Spawn position X
                                                this->player->getPosition().y, //Spawn position Y
                                                (i-1)*0.1f, //Direction X
                                                -1.f, //Direction Y
                                                4.f)); //Projectile speed
                }
                else{
                    this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"],
                                                0.2f,//Scale
                                                this->player->getPosition().x + this->player->getBounds().width/2.f, //Spawn position X
                                                this->player->getPosition().y, //Spawn position Y
                                                i*-0.1f, //Direction X
                                                -1.f, //Direction Y
                                                4.f)); //Projectile speed
                }
            }

        }
        else{//Even number of projectiles
            for(int i=1; i<=this->player->getProjectileNumber(); i++){
                if(i%2==0){
                    this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"],
                                                0.2f,//Scale
                                                this->player->getPosition().x + this->player->getBounds().width/2.f, //Spawn position X
                                                this->player->getPosition().y, //Spawn position Y
                                                (i-1)*0.1f, //Direction X
                                                -1.f, //Direction Y
                                                4.f)); //Projectile speed
                }
                else{
                    this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"],
                                                0.2f,//Scale
                                                this->player->getPosition().x + this->player->getBounds().width/2.f, //Spawn position X
                                                this->player->getPosition().y, //Spawn position Y
                                                i*-0.1f, //Direction X
                                                -1.f, //Direction Y
                                                4.f)); //Projectile speed
                }
            }
        }
    }
}

void Game::updateProjectiles()
{
    unsigned  c=0;//Player projectile moving and culling
    for(int i=0; i<this->projectiles.size(); i++){
        projectiles[i]->update();
        if(projectiles[i]->getBounds().top + projectiles[i]->getBounds().height <= 0.f){
            delete this->projectiles.at(c);
            this->projectiles.erase(this->projectiles.begin()+c);
            c--;
        }
        c++;
    }
    unsigned  d=0;//Enemy projectile moving and culling
    for(int i=0; i<this->enemyProjectiles.size(); i++){
        enemyProjectiles[i]->update();
        if(enemyProjectiles[i]->getBounds().top >= this->window->getSize().y){
            delete this->enemyProjectiles.at(d);
            this->enemyProjectiles.erase(this->enemyProjectiles.begin()+d);
            d--;
        }
        d++;
    }
    unsigned  e=0;//Power ups moving and culling
    for(int i=0; i<this->powerUps.size(); i++){
        powerUps[i]->update();
        if(powerUps[i]->getBounds().top >= this->window->getSize().y){
            delete this->powerUps.at(e);
            this->powerUps.erase(this->powerUps.begin()+e);
            e--;
        }
        e++;
    }

    //ENEMYPROJECTILE/PLAYER COLLISION, Losing life
    bool projectileHit = false;
    for (size_t k = 0; k < this->enemyProjectiles.size() && projectileHit == false; k++)
    {
        if (this->player->getBounds().intersects(this->enemyProjectiles[k]->getBounds()))
        {

            this->player->losingLife();
            this->scoreMulti = 1.f;
            this->scoreMultiCounter = 0.f;
            delete this->enemyProjectiles[k];
            this->enemyProjectiles.erase(this->enemyProjectiles.begin() + k);

            projectileHit = true;
        }
    }

    bool powerUpPicked = false;
    for (size_t k = 0; k < this->powerUps.size() && powerUpPicked == false; k++)
    {
        if (this->player->getBounds().intersects(this->powerUps[k]->getBounds()))
        {
            switch (powerUps[k]->getType()) {
            case 'H':
                this->player->gettingLife();
                break;
            case 'D':
                this->player->gettingDamage();
                break;
            case '+':
                this->player->gettingProjectiles();
                break;
            case 'A':
                this->player->updateAbility();
                break;
            }
            delete this->powerUps[k];
            this->powerUps.erase(this->powerUps.begin() + k);

            powerUpPicked = true;
        }
    }
}

void Game::updateEnemies()
{
    for (int i = 0; i < this->enemies.size(); ++i)
        {
        enemies[i]->update();
        //Boss specific stuff
        if(enemies[i]->getType()==2 && this->enemies[i]->phaseAvailable()){
            enemies[i]->changePhase(this->enemies[i]->getCurrentPhase());
        }

        //ENEMIES SHOOTING
        if(this->enemies[i]->attackAvailable()){
            float angle = (rand()%10+20)/100.f;
            if(this->enemies[i]->getProjectileNumber()%2==1){//Odd number of projectiles, middle projectile first
                this->enemyProjectiles.push_back(new Projectile(this->textures["ENEMYPROJ1"],
                                                 0.25f,//Scale
                                                 this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                 this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                 0.f, //Direction X
                                                 1.f, //Direction Y
                                                 this->enemies[i]->getProjectileSpeed())); //Projectile speed
                for(int n=1; n<this->enemies[i]->getProjectileNumber(); n++){
                    if(n%2==0){
                        this->enemyProjectiles.push_back(new Projectile(this->textures["ENEMYPROJ1"],
                                                         0.25f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         (n-1)*angle, //Direction X
                                                         1.f, //Direction Y
                                                         this->enemies[i]->getProjectileSpeed())); //Projectile speed
                    }
                    else{
                        this->enemyProjectiles.push_back(new Projectile(this->textures["ENEMYPROJ1"],
                                                         0.25f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         n*-angle, //Direction X
                                                         1.f, //Direction Y
                                                         this->enemies[i]->getProjectileSpeed())); //Projectile speed
                    }
                }

            }
            else{//Even number of projectiles
                for(int n=1; n<=this->enemies[i]->getProjectileNumber(); n++){
                    if(n%2==0){
                        this->enemyProjectiles.push_back(new Projectile(this->textures["ENEMYPROJ1"],
                                                         0.25f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         (n-1)*angle, //Direction X
                                                         1.f, //Direction Y
                                                         this->enemies[i]->getProjectileSpeed())); //Projectile speed
                    }
                    else{
                        this->enemyProjectiles.push_back(new Projectile(this->textures["ENEMYPROJ1"],
                                                         0.25f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         n*-angle, //Direction X
                                                         1.f, //Direction Y
                                                         this->enemies[i]->getProjectileSpeed())); //Projectile speed
                    }
                }
            }
        }
            //PROJECTILE/ENEMIES COLLISION, Killing enemies
            bool enemy_deleted = false;
            for (size_t k = 0; k < this->projectiles.size() && enemy_deleted == false; k++)
            {
                if (this->enemies[i]->getBounds().intersects(this->projectiles[k]->getBounds()))
                {

                    if(this->enemies[i]->getLife()<=0){
                        this->points += this->enemies[i]->getPoints()*scoreMulti;//Getting points
                        //Powerup drop
                        if(rand()%10<3){//Powerup drop chance - 30%
                            switch(rand()%4){
                            case 0://HP
                                this->powerUps.push_back(new Projectile(this->textures["HPPACK"],
                                                         1.f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         0.f, //Direction X
                                                         1.f, //Direction Y
                                                         0.75f, //Projectile speed
                                                         'H')); //Type
                                break;
                            case 1://DMG
                                this->powerUps.push_back(new Projectile(this->textures["DMGUP"],
                                                         1.f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         0.f, //Direction X
                                                         1.f, //Direction Y
                                                         0.75f, //Projectile speed
                                                         'D')); //Type
                                break;
                            case 2://+PROJ
                                this->powerUps.push_back(new Projectile(this->textures["PROJUP"],
                                                         1.f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         0.f, //Direction X
                                                         1.f, //Direction Y
                                                         0.75f, //Projectile speed
                                                         '+')); //Type
                                break;
                            case 3://POWER
                                this->powerUps.push_back(new Projectile(this->textures["BATTERY"],
                                                         1.f,//Scale
                                                         this->enemies[i]->getPosition().x + this->enemies[i]->getBounds().width/2.f, //Spawn position X
                                                         this->enemies[i]->getPosition().y + this->enemies[i]->getBounds().height, //Spawn position Y
                                                         0.f, //Direction X
                                                         1.f, //Direction Y
                                                         0.75f, //Projectile speed
                                                         'A')); //Type
                                break;
                            }
                        }
                        delete this->enemies[i];
                        this->enemies.erase(this->enemies.begin() + i);
                    }
                    else{
                        this->enemies[i]->losingLife(this->player->getDamage());
                    }

                    delete this->projectiles[k];
                    this->projectiles.erase(this->projectiles.begin() + k);

                    enemy_deleted = true;
                }
            }
        }
}

void Game::updateCollision()
{
    //Collision with left side
    if(this->player->getBounds().left<0.f){
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    //Collision with right side
    else if(this->player->getBounds().left+this->player->getBounds().width>=this->window->getSize().x){
        this->player->setPosition(this->window->getSize().x-this->player->getBounds().width, this->player->getBounds().top);
    }

    //Collision with top side
    if(this->player->getBounds().top<0.f){
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    //Collision with bottom side
    else if(this->player->getBounds().top+this->player->getBounds().height>=this->window->getSize().y){
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y-this->player->getBounds().height);
    }
}

void Game::updateUI()
{
    this->pointsText.setString("SCORE: " + std::to_string(this->points));
    this->scoreMultiText.setString("MULTI: " + std::to_string(this->scoreMulti).substr(0,std::to_string(this->scoreMulti).find('.')+3) + "x");
    this->livesText.setString("LIVES: " + std::to_string(this->player->getLives()));
    float abilityUsed = static_cast<float>(this->player->getAbilityCd())/this->player->getAbilityCdMax();
    this->abilityBar.setSize(sf::Vector2f(250.f * abilityUsed, this->abilityBar.getSize().y));
}

void Game::update()
{
    this->updateEvents();
    if(this->player->getLives()>0&&this->levelNumber<10){
        this->updatePlayerInput();
        this->player->update();
        this->updateProjectiles();
        this->updateEnemies();
        this->updateLevel();
        this->updateCollision();
        this->scoreMultiIncrease();
    }
   this->updateUI();
}


void Game::render()
{
    this->window->clear();
    //Draw start

    this->window->draw(this->backgroundSprite);
    this->player->render(*this->window);
    for(auto *i : this->enemies){
        i->render(this->window);
    }
    for(auto *i : this->projectiles){
        i->render(this->window);
    }
    for(auto *i : this->enemyProjectiles){
        i->render(this->window);
    }
    for(auto *i : this->powerUps){
        i->render(this->window);
    }
    this->window->draw(this->pointsText);
    this->window->draw(this->scoreMultiText);
    this->window->draw(this->livesText);
    this->window->draw(this->abilityBarBack);
    this->window->draw(this->abilityBar);
    if(this->player->getLives()<=0){
        this->window->draw(this->gameOverText);
    }
    if(levelNumber>=10){
        this->window->draw(this->victoryText);
    }


    //Draw end
    this->window->display();
}


