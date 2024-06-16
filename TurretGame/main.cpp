#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//finsh turret ablitlies (one does faster special atks)
//firebomb childf of bomb
//make a clean vector function for visual effectrs manmager
//more enemis
//different projectiles
//make damage spalsh
//texureStill for non looping textures (but still ned rotation)maybe
//make function in game that handles interactions between collision and enemy OR make a switch staement in HandleCollsions.
//use a loop in the texture.cpp so you can just add name of file and be done.
//resolve warnings
//enemies can drop abilities that can be clicked
//splash damage bullety
//move db to sep file
//make ability charges vbar on AbilityButton be handled in game instead of the button