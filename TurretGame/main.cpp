#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//make it so theres maxHealth and currenthealth where curetnhealth sytarts as max health
// //add a kb effect (different bullets have differnt kbs) differnte eminimes have difrfernt kb multipliers
//bg image
//game class
//create enemy
//different projectiles
// void ShootProjectile(std::vector<Bullet*>& projectiles); //TAKE BULLET ID AS PARAM TO SHOOT TYPES
//explosion texture when hit