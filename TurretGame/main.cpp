#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}


//make upgrade buttons constant size
//give seperate textures to each bullet
//decoration vector in levelhandler
//optimize Hotbar::GetActiveAbilityButtons()
//resolve warnings
//ability not ready / no charges splashes
//make upgrade to ice increase size
//make upgrade to bomb increase size/dmg

//enemies can drop abilities that can be clicked
//splash damage bullety
//make ability charges vbar on AbilityButton be handled in game instead of the button
//draw effec ton turret when ability is activated
//firebomb childf of bomb
//SENTRIES