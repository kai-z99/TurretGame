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
//resolve wanings
// 
//make each level have different bgs based on world
// 
//SENTRIES shoot closest enemy
// 
// 1. linearly scan all active enemies, find the closest one. Make a Sentry(), (child of turret) and set its angle using GetAngle with p1 at Sentry, p2 at closest enemy.
// 2. choose a burst of bullets based on the sentry state. Or shoots laser periodically?
// 
// 
// 
//enemies can drop abilities that can be clicked? maybe for later
//splash damage bullet, uses small scale bombExplosionMaybe? or a new AreaEffect called buulletexplosion.
//draw effec ton turret when ability is activated
//fix bug where no charges availible shows after using ice or bomb
// 
//add a trail to turretbullet
//make worldObject class and store them in worldojects in game. The chidren are decoration, levelButton, and worldMarker. The thing they ahve in common is they scroll
//rebalnce health/dmg so basic enemy has 100.0f health.

//idea: quad tree implementation in seperate project, just a visualizer of algs.