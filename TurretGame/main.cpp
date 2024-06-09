#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//more enemis
//different projectiles
//make damage spalsh
//texureStill for non looping textures (but still ned rotation)maybe
//make function in game that handles interactions between collision and enemy OR make a switch staement in HandleCollsions.
//use a loop in the texture.cpp so you can just add name of file and be done.
//resolve warnings
//enemies can drop abilities that can be clicked
//splash damage bullety