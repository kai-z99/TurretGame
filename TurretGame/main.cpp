#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//texureStill for non looping textures (but still ned rotation)maybe
//handle button clicking on hotbar (NOTE when in other input more this wont update so it will get stuck in a blue background after clikcing bomb or ice)
//create collision manager so game doesnt need access to enemy children
////THIS SHOULD BE IN VISUAL EFFECTS MANAGER void DrawVisualEffects(); this can have a game pointer, its ok.
//optimize Hotbar::GetActiveAbilityButtons()

//resolve warnings
//enemies can drop abilities that can be clicked
//splash damage bullety
//move db to sep file
//make ability charges vbar on AbilityButton be handled in game instead of the button
//draw effec ton turret when ability is activated
//firebomb childf of bomb