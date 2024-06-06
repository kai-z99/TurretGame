#include "raylib.h"
#include "Game.h"


int main(void)
{
    Game game = Game();
    game.Run();

    return 0;

}

//more enemis
//different projectiles
//explosion texture when hit
//make damage spalsh
//coin splash
//make text const vars in class
//add enums
//texureStill for non looping textures (but still ned rotation)maybe
//make function in game that handles interactions between collision and enemy OR make a switch staement in HandleCollsions.
//bool inRapidfire in turret
//IN HANDLEINPUT()  //check if each button isPressed. If it is, handle the event like rapidfire or something
//use a loop in the texture.cpp so you can just add name of file and be done.
//THE PROGRESS BARS IN TOP BUTTONS CAN REPRESENT COOLDOWNS FOR ABNLITLIES.