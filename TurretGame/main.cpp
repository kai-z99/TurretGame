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
// ability sounds already started, check sound handler
//laser sound, "HandleMiscSounds" in level handler OR just no func and handle it directly in update
//"Base Tint"
//
// Sound effect overlap system: "maxSounds"
// 
// 
// MUSIC
// 
// level progress bar
//resolve wanings
// 
//shop button, more back buttons
//
// title screen
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