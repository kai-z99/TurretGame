#include "Database.h"

//DEFAULT VALUES OF TURRET ABLITIES
std::unordered_map<TurretAbility, AbilityInfo> initialAbilityValues = 
{
    // type, {cooldown, lastshotframe, maxcharges, charges}
    {Rapidfire, {550, INT_MIN, 5, 5}},
    {Laser, {700, INT_MIN, 3, 3}},
    {Explosive, {800, INT_MIN, 2, 2}},
    {Ice, {750, INT_MIN, 5, 5}},
    {Clone, {550, INT_MIN, 5, 5}},
    {Burn, {550, INT_MIN, 5, 5}}
};