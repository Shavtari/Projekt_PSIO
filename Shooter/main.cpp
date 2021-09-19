#include <iostream>
#include <game.h>
#include <time.h>
using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    //srand(time(static_cast<unsigned>(0)));

    Game game;

    //Game loop
    while(game.isRunning()){
        //Updates
        game.update();
        //Render
        game.render();
    }

    return 0;
}
