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
//hook try again button up
//make lighting bullet that chains. recruse? void ActivateLightning(Enemy* e). 
// 
// 1. set enemylightning
// 2. if there is a enemy close enough thats active and no lightning, ActivateLightning(closeEnemy)
// 3. keep going until no enemy is close enough
// 4. Now use linear scan in UseDetonateLightning() on all enemies, damaging them.
// 5. creates a point on each enemy location, then draws line between each pair using a for loop. eg: 3 points is 2 lines.
// 
// 
//resolve wanings
//make each level have different bgs based on world
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