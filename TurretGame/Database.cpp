#include "Database.h"

#include <iostream>

//UPGRADES

namespace UpgradeDatabase
{
    const std::unordered_map<Upgrade, std::pair<int, int>> INITIAL_UPGRADE_INFO =
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

    const std::unordered_map<int, float> BULLET_FIRERATE_INCREASE_AMOUNTS =
    {
        {1, 0.2f},
        {2, 0.4f},
        {3, 0.6f},
        {4, 0.8f},
        {5, 1.0f},
        {6, 1.2f},
    };

    const int INITIAL_COINS = 0;
    const int INITIAL_STARTING_HEALTH = 30;

    //-------------------To be loaded to file----------------------------------//
    //----------------------------------------------------------------------------
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

    int totalCoins = 0;
    int startingHealth = 30;
    //----------------------------------------------------------------------------
}


//ABILITIES

namespace AbilityDatabase
{
    const std::unordered_map<TurretAbility, int> ABILITY_COOLDOWNS =
    {
        { Rapidfire,           550 },
        { Laser,               700 },
        { Ice,                 750 },
        { Explosive,           800 },
        { Clone,               1000 },
    }; 
}

namespace DBFunctions
{
    void LoadDatabaseFromFile(const char* filename)
    {
        std::ifstream file(filename);

        if (file.is_open())
        {
            json j;
            file >> j;
            file.close();

            // load currentUpgradeInfo

            for (const auto& [upgrade, info] : j["upgrades"].items())
            {
                Upgrade u = (Upgrade)(std::stoi(upgrade)); //convert from string to integer
                std::pair<int, int> i = { info[0] , info[1] }; //convert from json array element to int pair

                UpgradeDatabase::currentUpgradeInfo[u] = i;
            }

            // Load totalCoins
            UpgradeDatabase::totalCoins = j["coins"];

            // Load startingHealth
            UpgradeDatabase::startingHealth = j["hp"];

            std::cout << "Data found. Database loaded.\n";
        }

        else
        {
            std::cout << "Cannot find data. NO database to load.\n";
        }


    }

    void SaveDatabaseToFile(const char* filename)
    {
        json j =
        {
            {"coins",UpgradeDatabase::totalCoins},
            {"hp", UpgradeDatabase::startingHealth},
            {"upgrades", json::object()},

        };

        for (const auto& [upgrade, info] : UpgradeDatabase::currentUpgradeInfo)
        {
            auto& [level, price] = info;
            j["upgrades"][std::to_string(upgrade)] = { level,price }; // pair converted to json array.
        }

        std::ofstream file(filename);

        if (file.is_open())
        {
            file << j.dump(4); // Pretty print with 4 spaces
            file.close();

            std::cout << "Data saved.\n";
        }

        else
        {
            std::cout << "Could not open data file. Data not saved.\n";
        }
    }

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

