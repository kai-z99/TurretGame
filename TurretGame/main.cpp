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
// fix jittering of reposition in balloon. use abs to fix this
// 
// make text button vary in size
//clones deal less dmg/kb than main
//"Base Tint"
//change button to have isReleased, isDown, isHovering, isPressed
// 
//resolve wanings
// 
//make each level have different bgs based on world
//
// 
// 
//enemies can drop abilities that can be clicked? maybe for later
//splash damage bullet, uses small scale bombExplosionMaybe? or a new AreaEffect called buulletexplosion.
//draw different effects when ability is activated
//fix bug where no charges availible shows after using ice or bomb
// 
//add a trail to turretbullet
//make worldObject class and store them in worldojects in game. The chidren are decoration, levelButton, and worldMarker. The thing they ahve in common is they scroll
//rebalnce health/dmg so basic enemy has 100.0f health.

//idea: quad tree implementation