#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//hook try again button up
//new bullet
//decoration vector in levelhandler
//optimize Hotbar::GetActiveAbilityButtons()
//resolve warnings

//enemies can drop abilities that can be clicked
//splash damage bullety
//draw effec ton turret when ability is activated
//firebomb childf of bomb
//SENTRIES
// add a trail to turretbullet
//make worldObject class and store them in worldojects in game. The chidren are decoration, levelButton, and worldMarker. The thing they ahve in common is they scroll