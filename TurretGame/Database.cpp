#include "Database.h"


//UPGRADES

namespace UpgradeDatabase
{
    const std::unordered_map<Upgrade, std::pair<int, int>> initalUpgradeInfo =
    {
        { TurretBulletU,        {1, 50  } },
        { ShockwaveBulletU,     {0, 100 } },
        { FireBulletU,          {0, 1000} },
        { SniperBulletU,        {0, 2000} },
        { LightningBulletU,     {0, 3000} },
        { BombBulletU,          {0, 5000} },
        { RapidfireU,           {1, 300 } },
        { LaserU,               {0, 850 } },
        { IceU,                 {0, 2150} },
        { ExplosiveU,           {0, 3100} },
        { CloneU,               {0, 5150} },
    };

    std::unordered_map<Upgrade, std::pair<int, int>> currentUpgradeInfo =
    {
        { TurretBulletU,        {1, 50  } },
        { ShockwaveBulletU,     {0, 100 } },
        { FireBulletU,          {0, 1000} },
        { SniperBulletU,        {0, 2000} },
        { LightningBulletU,     {0, 3000} },
        { BombBulletU,          {0, 5000} },
        { RapidfireU,           {1, 300 } },
        { LaserU,               {0, 850 } },
        { IceU,                 {0, 2150} },
        { ExplosiveU,           {0, 3100} },
        { CloneU,               {0, 5150} },
    };
}


//ABILITIES

namespace AbilityDatabase
{
    const std::unordered_map<TurretAbility, int> abilityCooldowns =
    {
        { Rapidfire,           550 },
        { Laser,               700 },
        { Ice,                 750 },
        { Explosive,           800 },
        { Clone,               100 },
    };


    std::unordered_map<TurretAbility, short> GetRoundStartAbilityCharges()
    {
        std::unordered_map<TurretAbility, short> data;

        //if level is 0, no charges. else its 1 + 1 every 4 levels
        (UpgradeDatabase::currentUpgradeInfo[RapidfireU].first > 0) ? data[Rapidfire] = 1 + UpgradeDatabase::currentUpgradeInfo[RapidfireU].first / 4 : data[Rapidfire] = 0;
        (UpgradeDatabase::currentUpgradeInfo[LaserU].first > 0)     ? data[Laser] = 1 + UpgradeDatabase::currentUpgradeInfo[LaserU].first / 4         : data[Laser]     = 0;
        (UpgradeDatabase::currentUpgradeInfo[IceU].first > 0)       ? data[Ice] = 1 + UpgradeDatabase::currentUpgradeInfo[IceU].first / 4             : data[Ice]       = 0;
        (UpgradeDatabase::currentUpgradeInfo[ExplosiveU].first > 0) ? data[Explosive] = 1 + UpgradeDatabase::currentUpgradeInfo[ExplosiveU].first / 4 : data[Explosive] = 0;
        (UpgradeDatabase::currentUpgradeInfo[CloneU].first > 0)     ? data[Clone] = 1 + UpgradeDatabase::currentUpgradeInfo[CloneU].first / 4         : data[Clone]     = 0;

        return data;
    }
}

