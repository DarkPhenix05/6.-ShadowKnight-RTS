#include "map"
#include "Miner.h"
#pragma once

class GameManager
{
public:
    void addMiner(Miner miner);
    void removeMiner(Miner miner);
public:
    std::map<int,Miner> Miners;
};
