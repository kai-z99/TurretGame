#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//prevent scrolling past first level
//new bullet
//decoration vector in levelhandler
//optimize Hotbar::GetActiveAbilityButtons()
//resolve warnings
//ability not ready / no charges splashes
//lock menu scolling to x axis, set world transitions. World borders are defined in constants

//enemies can drop abilities that can be clicked
//splash damage bullety
//draw effec ton turret when ability is activated
//firebomb childf of bomb
//SENTRIES