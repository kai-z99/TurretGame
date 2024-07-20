#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

// Refrain from front-end detailing until engine is finished.
// 
//
//
//"Base Tint"
//
// 
//
// finish db implementation. dont worry about progress save just yet. just finish making the game use it like upgrade changes db instead of games state. 
// then games state uses db to update
// 
// defeat enemy sound
// 
// database page
// 
//resolve wanings
// 
// levels compelte in gamestats. another db item.
//
//
// 
//enemies can drop abilities that can be clicked? maybe for later
//
//
//draw different effects when ability is activated
//fix bug where no charges availible shows after using ice or bomb
// 
//add a trail to turretbullet
//make worldObject class and store them in worldojects in game. The chidren are decoration, levelButton, and worldMarker. The thing they ahve in common is they scroll
//rebalnce health/dmg so basic enemy has 100.0f health.

//idea: quad tree implementation